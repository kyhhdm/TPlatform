// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.1

package mapreduce.slice;

public final class MapReduceJob implements java.lang.Cloneable
{
    public String inputFile;

    public String outputFile;

    public int outputReplication;

    public String soFile;

    public int mapTaskNum;

    public int reduceTaskNum;

    public boolean doLocalCombine;

    public boolean doGroupBySort;

    public boolean doConcatOutputs;

    public String mapperClass;

    public String reducerClass;

    public String mapperOutKeyClass;

    public String mapperOutValueClass;

    public String mapperInKeyClass;

    public String mapperInValueClass;

    public String mapperRecordReaderClass;

    public String reducerOutKeyClass;

    public String reducerOutValueClass;

    public String reducerRecordWriterClass;

    public MapReduceJob()
    {
    }

    public MapReduceJob(String inputFile, String outputFile, int outputReplication, String soFile, int mapTaskNum, int reduceTaskNum, boolean doLocalCombine, boolean doGroupBySort, boolean doConcatOutputs, String mapperClass, String reducerClass, String mapperOutKeyClass, String mapperOutValueClass, String mapperInKeyClass, String mapperInValueClass, String mapperRecordReaderClass, String reducerOutKeyClass, String reducerOutValueClass, String reducerRecordWriterClass)
    {
	this.inputFile = inputFile;
	this.outputFile = outputFile;
	this.outputReplication = outputReplication;
	this.soFile = soFile;
	this.mapTaskNum = mapTaskNum;
	this.reduceTaskNum = reduceTaskNum;
	this.doLocalCombine = doLocalCombine;
	this.doGroupBySort = doGroupBySort;
	this.doConcatOutputs = doConcatOutputs;
	this.mapperClass = mapperClass;
	this.reducerClass = reducerClass;
	this.mapperOutKeyClass = mapperOutKeyClass;
	this.mapperOutValueClass = mapperOutValueClass;
	this.mapperInKeyClass = mapperInKeyClass;
	this.mapperInValueClass = mapperInValueClass;
	this.mapperRecordReaderClass = mapperRecordReaderClass;
	this.reducerOutKeyClass = reducerOutKeyClass;
	this.reducerOutValueClass = reducerOutValueClass;
	this.reducerRecordWriterClass = reducerRecordWriterClass;
    }

    public boolean
    equals(java.lang.Object rhs)
    {
	if(this == rhs)
	{
	    return true;
	}
	MapReduceJob _r = null;
	try
	{
	    _r = (MapReduceJob)rhs;
	}
	catch(ClassCastException ex)
	{
	}

	if(_r != null)
	{
	    if(inputFile != _r.inputFile && inputFile != null && !inputFile.equals(_r.inputFile))
	    {
		return false;
	    }
	    if(outputFile != _r.outputFile && outputFile != null && !outputFile.equals(_r.outputFile))
	    {
		return false;
	    }
	    if(outputReplication != _r.outputReplication)
	    {
		return false;
	    }
	    if(soFile != _r.soFile && soFile != null && !soFile.equals(_r.soFile))
	    {
		return false;
	    }
	    if(mapTaskNum != _r.mapTaskNum)
	    {
		return false;
	    }
	    if(reduceTaskNum != _r.reduceTaskNum)
	    {
		return false;
	    }
	    if(doLocalCombine != _r.doLocalCombine)
	    {
		return false;
	    }
	    if(doGroupBySort != _r.doGroupBySort)
	    {
		return false;
	    }
	    if(doConcatOutputs != _r.doConcatOutputs)
	    {
		return false;
	    }
	    if(mapperClass != _r.mapperClass && mapperClass != null && !mapperClass.equals(_r.mapperClass))
	    {
		return false;
	    }
	    if(reducerClass != _r.reducerClass && reducerClass != null && !reducerClass.equals(_r.reducerClass))
	    {
		return false;
	    }
	    if(mapperOutKeyClass != _r.mapperOutKeyClass && mapperOutKeyClass != null && !mapperOutKeyClass.equals(_r.mapperOutKeyClass))
	    {
		return false;
	    }
	    if(mapperOutValueClass != _r.mapperOutValueClass && mapperOutValueClass != null && !mapperOutValueClass.equals(_r.mapperOutValueClass))
	    {
		return false;
	    }
	    if(mapperInKeyClass != _r.mapperInKeyClass && mapperInKeyClass != null && !mapperInKeyClass.equals(_r.mapperInKeyClass))
	    {
		return false;
	    }
	    if(mapperInValueClass != _r.mapperInValueClass && mapperInValueClass != null && !mapperInValueClass.equals(_r.mapperInValueClass))
	    {
		return false;
	    }
	    if(mapperRecordReaderClass != _r.mapperRecordReaderClass && mapperRecordReaderClass != null && !mapperRecordReaderClass.equals(_r.mapperRecordReaderClass))
	    {
		return false;
	    }
	    if(reducerOutKeyClass != _r.reducerOutKeyClass && reducerOutKeyClass != null && !reducerOutKeyClass.equals(_r.reducerOutKeyClass))
	    {
		return false;
	    }
	    if(reducerOutValueClass != _r.reducerOutValueClass && reducerOutValueClass != null && !reducerOutValueClass.equals(_r.reducerOutValueClass))
	    {
		return false;
	    }
	    if(reducerRecordWriterClass != _r.reducerRecordWriterClass && reducerRecordWriterClass != null && !reducerRecordWriterClass.equals(_r.reducerRecordWriterClass))
	    {
		return false;
	    }

	    return true;
	}

	return false;
    }

    public int
    hashCode()
    {
	int __h = 0;
	if(inputFile != null)
	{
	    __h = 5 * __h + inputFile.hashCode();
	}
	if(outputFile != null)
	{
	    __h = 5 * __h + outputFile.hashCode();
	}
	__h = 5 * __h + outputReplication;
	if(soFile != null)
	{
	    __h = 5 * __h + soFile.hashCode();
	}
	__h = 5 * __h + mapTaskNum;
	__h = 5 * __h + reduceTaskNum;
	__h = 5 * __h + (doLocalCombine ? 1 : 0);
	__h = 5 * __h + (doGroupBySort ? 1 : 0);
	__h = 5 * __h + (doConcatOutputs ? 1 : 0);
	if(mapperClass != null)
	{
	    __h = 5 * __h + mapperClass.hashCode();
	}
	if(reducerClass != null)
	{
	    __h = 5 * __h + reducerClass.hashCode();
	}
	if(mapperOutKeyClass != null)
	{
	    __h = 5 * __h + mapperOutKeyClass.hashCode();
	}
	if(mapperOutValueClass != null)
	{
	    __h = 5 * __h + mapperOutValueClass.hashCode();
	}
	if(mapperInKeyClass != null)
	{
	    __h = 5 * __h + mapperInKeyClass.hashCode();
	}
	if(mapperInValueClass != null)
	{
	    __h = 5 * __h + mapperInValueClass.hashCode();
	}
	if(mapperRecordReaderClass != null)
	{
	    __h = 5 * __h + mapperRecordReaderClass.hashCode();
	}
	if(reducerOutKeyClass != null)
	{
	    __h = 5 * __h + reducerOutKeyClass.hashCode();
	}
	if(reducerOutValueClass != null)
	{
	    __h = 5 * __h + reducerOutValueClass.hashCode();
	}
	if(reducerRecordWriterClass != null)
	{
	    __h = 5 * __h + reducerRecordWriterClass.hashCode();
	}
	return __h;
    }

    public java.lang.Object
    clone()
    {
	java.lang.Object o = null;
	try
	{
	    o = super.clone();
	}
	catch(CloneNotSupportedException ex)
	{
	    assert false; // impossible
	}
	return o;
    }

    public void
    __write(IceInternal.BasicStream __os)
    {
	__os.writeString(inputFile);
	__os.writeString(outputFile);
	__os.writeInt(outputReplication);
	__os.writeString(soFile);
	__os.writeInt(mapTaskNum);
	__os.writeInt(reduceTaskNum);
	__os.writeBool(doLocalCombine);
	__os.writeBool(doGroupBySort);
	__os.writeBool(doConcatOutputs);
	__os.writeString(mapperClass);
	__os.writeString(reducerClass);
	__os.writeString(mapperOutKeyClass);
	__os.writeString(mapperOutValueClass);
	__os.writeString(mapperInKeyClass);
	__os.writeString(mapperInValueClass);
	__os.writeString(mapperRecordReaderClass);
	__os.writeString(reducerOutKeyClass);
	__os.writeString(reducerOutValueClass);
	__os.writeString(reducerRecordWriterClass);
    }

    public void
    __read(IceInternal.BasicStream __is)
    {
	inputFile = __is.readString();
	outputFile = __is.readString();
	outputReplication = __is.readInt();
	soFile = __is.readString();
	mapTaskNum = __is.readInt();
	reduceTaskNum = __is.readInt();
	doLocalCombine = __is.readBool();
	doGroupBySort = __is.readBool();
	doConcatOutputs = __is.readBool();
	mapperClass = __is.readString();
	reducerClass = __is.readString();
	mapperOutKeyClass = __is.readString();
	mapperOutValueClass = __is.readString();
	mapperInKeyClass = __is.readString();
	mapperInValueClass = __is.readString();
	mapperRecordReaderClass = __is.readString();
	reducerOutKeyClass = __is.readString();
	reducerOutValueClass = __is.readString();
	reducerRecordWriterClass = __is.readString();
    }
}
