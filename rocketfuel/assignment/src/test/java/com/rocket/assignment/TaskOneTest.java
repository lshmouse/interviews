package com.rocket.assignment;

import static org.junit.Assert.*;

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

public class TaskOneTest {

	MapDriver<Object, Text, LongWritable, LongWritable> mapDriver;
	ReduceDriver<LongWritable, LongWritable, LongWritable, Text> reduceDriver;
	MapReduceDriver<Object, Text, LongWritable, LongWritable, LongWritable, Text> mapReduceDriver;

	@Before
	public void setUp() {
		TaskOne.TokenizerMapper mapper = new TaskOne.TokenizerMapper();
		TaskOne.TaskOneReducer reducer = new TaskOne.TaskOneReducer();
		mapDriver = MapDriver.newMapDriver(mapper);
		reduceDriver = ReduceDriver.newReduceDriver(reducer);
		mapReduceDriver = MapReduceDriver.newMapReduceDriver(mapper, reducer);
	}

	@Test
	public void testMapper() throws IOException {
		mapDriver.withInput(new Text(), new Text("click\t123\t123\txxx"))
				.withInput(new Text(), new Text("other\t123\t456\txxx"))
				.withOutput(new LongWritable(123), new LongWritable(123))
				.withOutput(new LongWritable(123), new LongWritable(456))
				.runTest();

		assertEquals("Expected 3 record counter", 2, mapDriver.getCounters()
				.findCounter(TaskOne.TaskOneCounter.RecordsNum).getValue());
	}

	@Test
	public void testReducer() throws IOException {
		List<LongWritable> values = new ArrayList<LongWritable>();
		values.add(new LongWritable(1));
		values.add(new LongWritable(5));
		values.add(new LongWritable(10));

		reduceDriver.withInput(new LongWritable(123), values)
				.withInput(new LongWritable(456), values)
				.withOutput(new LongWritable(123), new Text("123\t9"))
				.withOutput(new LongWritable(456), new Text("456\t9"))
				.runTest();

		assertEquals("Expected 2 counter increment", 2, reduceDriver
				.getCounters().findCounter(TaskOne.TaskOneCounter.UsersNum)
				.getValue());
	}

	@Test
	public void testMapReduce() throws IOException {
		mapReduceDriver.withInput(new Text(), new Text("click\t123\t123\txxx"))
				.withInput(new Text(), new Text("other\t123\t456\txxx"))
				.withInput(new Text(), new Text("click\t456\t123\txxx"))
				.withInput(new Text(), new Text("view\t456\t456\txxx"));

		// output key should be in order
		mapReduceDriver
				.withOutput(new LongWritable(123), new Text("123\t333"))
				.withOutput(new LongWritable(456), new Text("456\t333"))
				.runTest();
	}
}