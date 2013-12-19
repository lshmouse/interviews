package com.rocket.assignment;

import static org.junit.Assert.assertEquals;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mrunit.mapreduce.MapDriver;
import org.apache.hadoop.mrunit.mapreduce.MapReduceDriver;
import org.apache.hadoop.mrunit.mapreduce.ReduceDriver;
import org.junit.Before;
import org.junit.Test;

public class TaskTwoTest {
	MapDriver<Object, Text, LongWritable, Text> mapDriver;
	ReduceDriver<LongWritable, Text, LongWritable, Text> reduceDriver;
	MapReduceDriver<Object, Text, LongWritable, Text, LongWritable, Text> mapReduceDriver;

	@Before
	public void setUp() {
		TaskTwo.TokenizerMapper mapper = new TaskTwo.TokenizerMapper();
		TaskTwo.TaskTwoReducer reducer = new TaskTwo.TaskTwoReducer();
		mapDriver = MapDriver.newMapDriver(mapper);
		reduceDriver = ReduceDriver.newReduceDriver(reducer);
		mapReduceDriver = MapReduceDriver.newMapReduceDriver(mapper, reducer);
	}

	@Test
	public void testMapper() throws IOException {
		mapDriver
				.withInput(new Text(), new Text("click\t123\t123\txxx"))
				.withInput(new Text(), new Text("other\t123\t789\txxx"))
				.withInput(new Text(), new Text("other\t123\t456\txxx"))
				.withOutput(new LongWritable(123), new Text("1:123"))
				.withOutput(new LongWritable(123),
						new Text("2:other\t123\t789\txxx"))
				.withOutput(new LongWritable(123),
						new Text("2:other\t123\t456\txxx")).runTest();

		assertEquals("Expected 3 record num", 3, mapDriver.getCounters()
				.findCounter(TaskTwo.TaskTwoCounter.RecordsNum).getValue());

		assertEquals(
				"Expected 1 view click record num",
				1,
				mapDriver
						.getCounters()
						.findCounter(TaskTwo.TaskTwoCounter.ViewClickRecordsNum)
						.getValue());

		assertEquals("Expected 2 other record num", 2, mapDriver.getCounters()
				.findCounter(TaskTwo.TaskTwoCounter.OtherRecordsNum).getValue());
	}

	@Test
	public void testReducer() throws IOException {
		List<Text> values = new ArrayList<Text>();
		values.add(new Text("1:1"));
		values.add(new Text("1:5"));
		values.add(new Text("1:10"));

		// mrunit donot support multi output now
		// values.add(new Text("2:other\t123\t456\txxx"));

		reduceDriver.withInput(new LongWritable(123), values)
				.withInput(new LongWritable(456), values)
				.withOutput(new LongWritable(123), new Text("123\t9"))
				.withOutput(new LongWritable(456), new Text("456\t9"))
				.runTest();

		assertEquals("Expected 2 counter increment", 2, reduceDriver
				.getCounters().findCounter(TaskTwo.TaskTwoCounter.UsersNum)
				.getValue());
	}

	@Test
	public void testMapReduce() throws IOException {
		mapReduceDriver.withInput(new Text(), new Text("click\t123\t123\txxx"))
				.withInput(new Text(), new Text("view\t123\t789\txxx"))
				.withInput(new Text(), new Text("click\t456\t123\txxx"))
				.withInput(new Text(), new Text("view\t456\t456\txxx"));

		// mrunit donot support multi output now
		// .withInput(new Text(), new Text("other\t123\t456\txxx"))

		mapReduceDriver.withOutput(new LongWritable(123), new Text("123\t666"))
				.withOutput(new LongWritable(456), new Text("456\t333"))
				.runTest();
	}
}