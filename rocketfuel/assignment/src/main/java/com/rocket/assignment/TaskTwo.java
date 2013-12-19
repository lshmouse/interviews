package com.rocket.assignment;

import java.io.IOException;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Counter;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.MultipleOutputs;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;

/**
 * input: log records. Schema: event_type STRING, user_id BIGINT,
 * event_unix_timestamp BIGINT, some_1k_data STRING \n
 * 
 * output: We would now like to find time elapsed as defined in task (1), but
 * only considering click and view events. We would also like all records with
 * 'other' event type written out to separate files for some post processing. \n
 * two output:
 * standard reducer output: Text:  user_id BIGINT\time elapsed BIGINT
 * otherRecords output: same format as input
 * 
 * @author liushaohui
 * 
 */
public class TaskTwo {

	public final static String OTHER_RECORDS_OUTPUT = "com.rocket.assignment.otherrecords.output";
	public final static String DATA_TYPE1 = "1:";
	public final static String DATA_TYPE2 = "2:";
	
	static enum TaskTwoCounter {
		BadRecord, RecordsNum, ViewClickRecordsNum, OtherRecordsNum, UsersNum
	};

	public static class TokenizerMapper extends
			Mapper<Object, Text, LongWritable, Text> {
		private Counter recordsNum;
		private Counter viewClickrecordsNum;
		private Counter otherRecordsNum;
		private Counter badRecordsNum;

		protected void setup(Context context) throws IOException,
				InterruptedException {
			recordsNum = context.getCounter(TaskTwoCounter.RecordsNum);
			badRecordsNum = context.getCounter(TaskTwoCounter.BadRecord);
			viewClickrecordsNum = context
					.getCounter(TaskTwoCounter.ViewClickRecordsNum);
			otherRecordsNum = context
					.getCounter(TaskTwoCounter.OtherRecordsNum);
		}

		public void map(Object key, Text value, Context context)
				throws IOException, InterruptedException {
			// event_type STRING, user_id BIGINT, event_unix_timestamp BIGINT,
			// some_1k_data STRING
			String[] splits = value.toString().split("\t");
			if (splits.length <= 3) {
				badRecordsNum.increment(1);
				return;
			}
			try {
				String type = splits[0];
				Long userId = Long.parseLong(splits[1]);
				Long timestamp = Long.parseLong(splits[2]);
				if (type.compareTo("view") == 0 || type.compareTo("click") == 0) {
					context.write(new LongWritable(userId), new Text(DATA_TYPE1 + Long.toString(timestamp)));
					this.viewClickrecordsNum.increment(1);
				} else {
					this.otherRecordsNum.increment(1);
					context.write(new LongWritable(userId), new Text(DATA_TYPE2 + value.toString()));
				}
			} catch (NumberFormatException e) {
				badRecordsNum.increment(1);
				return;
			}
			recordsNum.increment(1);
		}
	}

	public static class TaskTwoCombiner extends
			Reducer<LongWritable, Text, LongWritable, Text> {

		public void reduce(LongWritable userId, Iterable<Text> values,
				Context context) throws IOException, InterruptedException {
			long minTs = 0;
			long maxTs = 0;
			boolean found = false;
			for (Text val : values) {
				String data = val.toString();
				if (data.startsWith(DATA_TYPE1)) {
					long ts = Long.parseLong(data.substring(DATA_TYPE1.length()));
					if (found) {
						minTs = Math.min(minTs, ts);
						maxTs = Math.max(maxTs, ts);
					} else {
						found = true;
						minTs = ts;
						maxTs = ts;
					}
				} else if (data.startsWith(DATA_TYPE2)){
					context.write(userId, val);
				}
			}
			context.write(userId, new Text(DATA_TYPE1 + Long.toString(minTs)));
			context.write(userId, new Text(DATA_TYPE1 + Long.toString(maxTs)));
		}
	}

	public static class TaskTwoReducer extends
			Reducer<LongWritable, Text, LongWritable, Text> {
		Counter usersNum;

		private MultipleOutputs<LongWritable, Text> multiOutputs;
		
		protected void setup(Context context) throws IOException,
				InterruptedException {
			usersNum = context.getCounter(TaskTwoCounter.UsersNum);
			multiOutputs = new MultipleOutputs<LongWritable, Text>(context);
		}

		public void reduce(LongWritable userId, Iterable<Text> values,
				Context context) throws IOException, InterruptedException {
			usersNum.increment(1);
			
			long minTs = 0;
			long maxTs = 0;
			boolean found = false;
			for (Text val : values) {
				String data = val.toString();
				if (data.startsWith(DATA_TYPE1)) {
					long ts = Long.parseLong(data.substring(DATA_TYPE1.length()));
					if (found) {
						minTs = Math.min(minTs, ts);
						maxTs = Math.max(maxTs, ts);
					} else {
						found = true;
						// minTs/maxTs init here
						minTs = ts;
						maxTs = ts;
					}
				} else if (data.startsWith(DATA_TYPE2)){
					multiOutputs.write("otherRecords", userId, new Text(data.substring(DATA_TYPE1.length())));
				}
			}

			StringBuilder sb = new StringBuilder();
			sb.append(Long.toString(userId.get())).append("\t");
			sb.append(Long.toString(maxTs - minTs));
			context.write(userId, new Text(sb.toString()));
			//multiOutputs.write("timeElapsed", userId, new Text(sb.toString()));			
		}
	}

	public static void main(String[] args) throws Exception {
		Configuration conf = new Configuration();
		// Use GenericOptionsParse, supporting -D -conf etc.
		String[] otherArgs = new GenericOptionsParser(conf, args)
				.getRemainingArgs();

		if (otherArgs.length != 2) {
			System.err
					.println("Usage: TaskTwo <input> <output>");
			System.exit(2);
		}
		String input = otherArgs[0];
		String output = otherArgs[1];

		System.out.println("Running framework: "
				+ conf.get("mapreduce.framework.name"));
		System.out.println("File system: " + conf.get("fs.default.name"));

		Job job = new Job(conf, "rocket-assigment-task-two");

		job.setJarByClass(TaskTwo.class);

		job.setMapperClass(TokenizerMapper.class);
		job.setCombinerClass(TaskTwoCombiner.class);
		job.setReducerClass(TaskTwoReducer.class);
		
		job.setOutputKeyClass(LongWritable.class);
		job.setOutputValueClass(Text.class);

		// Defines additional single text based output 'other-records' for the job
		MultipleOutputs.addNamedOutput(job, "otherRecords",
				TextOutputFormat.class, LongWritable.class, Text.class);

		FileInputFormat.addInputPath(job, new Path(input));
		FileOutputFormat.setOutputPath(job, new Path(output));

		System.exit(job.waitForCompletion(true) ? 0 : 1);
	}
}