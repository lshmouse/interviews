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
import org.apache.hadoop.util.GenericOptionsParser;

/**
 * input: log records. Schema: event_type STRING, user_id BIGINT,
 * event_unix_timestamp BIGINT, some_1k_data STRING \n
 * 
 * output: for each user, time elapsed between his/her first and last event. \n
 * The format is:Text:  user_id BIGINT\time elapsed BIGINT
 * 
 * @author liushaohui
 * 
 */
public class TaskOne {
	static enum TaskOneCounter {
		BadRecord, RecordsNum, UsersNum
	};

	public static class TokenizerMapper extends
			Mapper<Object, Text, LongWritable, LongWritable> {
		private Counter recordsNum;
		private Counter badRecords;

		protected void setup(Context context) throws IOException,
				InterruptedException {
			recordsNum = context.getCounter(TaskOneCounter.RecordsNum);
			badRecords = context.getCounter(TaskOneCounter.BadRecord);
		}

		public void map(Object key, Text value, Context context)
				throws IOException, InterruptedException {
			// event_type STRING, user_id BIGINT, event_unix_timestamp BIGINT,
			// some_1k_data STRING
			String[] splits = value.toString().split("\t");
			if (splits.length <= 3) {
				badRecords.increment(1);
				return;
			}
			try {
				// String type = splits[0];
				Long userId = Long.parseLong(splits[1]);
				Long timestamp = Long.parseLong(splits[2]);
				context.write(new LongWritable(userId), new LongWritable(
						timestamp));
			} catch (NumberFormatException e) {
				badRecords.increment(1);
				return;
			}
			recordsNum.increment(1);
		}
	}

	public static class TaskOneCombiner extends
			Reducer<LongWritable, LongWritable, LongWritable, LongWritable> {

		public void reduce(LongWritable userId, Iterable<LongWritable> values,
				Context context) throws IOException, InterruptedException {
			long minTs = values.iterator().next().get();
			long maxTs = values.iterator().next().get();

			for (LongWritable val : values) {
				minTs = Math.min(minTs, val.get());
				maxTs = Math.max(maxTs, val.get());
			}
			context.write(userId, new LongWritable(minTs));
			context.write(userId, new LongWritable(maxTs));
		}
	}

	public static class TaskOneReducer extends
			Reducer<LongWritable, LongWritable, LongWritable, Text> {
		Counter usersNum;
		boolean isReducer;

		protected void setup(Context context) throws IOException,
				InterruptedException {
			usersNum = context.getCounter(TaskOneCounter.UsersNum);
		}

		public void reduce(LongWritable userId, Iterable<LongWritable> values,
				Context context) throws IOException, InterruptedException {
			usersNum.increment(1);

			long minTs = values.iterator().next().get();
			long maxTs = values.iterator().next().get();

			for (LongWritable val : values) {
				minTs = Math.min(minTs, val.get());
				maxTs = Math.max(maxTs, val.get());
			}

			StringBuilder sb = new StringBuilder();
			sb.append(Long.toString(userId.get())).append("\t");
			sb.append(Long.toString(maxTs - minTs));
			
			context.write(userId, new Text(sb.toString()));
		}
	}

	public static void main(String[] args) throws Exception {
		Configuration conf = new Configuration();
		// Use GenericOptionsParse, supporting -D -conf etc.
		String[] otherArgs = new GenericOptionsParser(conf, args)
				.getRemainingArgs();

		if (otherArgs.length != 2) {
			System.err.println("Usage: taskone <input> <output>");
			System.exit(2);
		}
		String input = otherArgs[0];
		String output = otherArgs[1];

		System.out.println("Running framework: "
				+ conf.get("mapreduce.framework.name"));
		System.out.println("File system: " + conf.get("fs.default.name"));

		Job job = new Job(conf, "rocket-assigment-task-one");

		job.setJarByClass(TaskOne.class);
		job.setMapperClass(TokenizerMapper.class);
		job.setCombinerClass(TaskOneCombiner.class);
		job.setReducerClass(TaskOneReducer.class);

		job.setOutputKeyClass(LongWritable.class);
		job.setOutputValueClass(Text.class);

		FileInputFormat.addInputPath(job, new Path(input));
		FileOutputFormat.setOutputPath(job, new Path(output));

		System.exit(job.waitForCompletion(true) ? 0 : 1);
	}
}
