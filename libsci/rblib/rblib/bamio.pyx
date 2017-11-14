# -*- coding: UTF-8 -*-
import sys
import pysam
import mutilstats
import os

def coverage_cal(mergedregionlen,send,qstart,qend,add=1):
	# must use sorted bam
	# send is last pos for  end of now cover
	# qstart qend is alignment blocks subarr   [ )  0 - based 
	if send >= qend:pass
	else:
		mergedregionlen = mergedregionlen + qend - max(send,qstart)
		send = qend
	return mergedregionlen,send

def readsortbam(bamfile):
	## bammust be sorted 
	return 0

def gethits(read):
	nhits = 1
	if read.has_tag("NH"):
		nhits = read.get_tag("NH")
	elif read.has_tag("XA"):
		nhits = 3
	elif read.has_tag("SA"):
		nhits = 2
	return nhits
def FR_discordant(read):
	ret = 0
	if read.is_read1:
		if read.reference_id <> read.next_reference_id:
			ret = 1
		if read.is_reverse:
			if read.template_length >=0: ret = 1
		else:
			if read.template_length <=0: ret = 1
	return ret



def mappingstat(bamfile):
	totalreads  = 0 
	totalbases  = 0 
	totalmapped = 0 
	totalproper = 0 
	totalsingletons = 0 
	totalmapq5  = 0 
	totalmapq20 = 0 
	samfile = pysam.Samfile( bamfile, "rb" )
	mulhits  = 0 
	uniqhits = 0 
	lowmapq = 0 
	totaldiscordantly = 0 
	totaldup = 0 
	for read in samfile:
		if read.is_secondary:continue
		totalreads += 1
		totalbases += read.query_length
		if read.is_unmapped:continue
		if read.is_duplicate:
			totaldup += 1
		totalmapped += 1
		if read.mapq >= 20: 
			totalmapq20 += 1; totalmapq5 += 1
		elif read.mapq >= 5:
			totalmapq5 += 1
		else:lowmapq+=1
		if read.is_proper_pair: totalproper += 1
		nhits = gethits(read)
		if nhits >=2:
			mulhits += 1
		else:uniqhits += 1   
		if read.mate_is_unmapped: 
			totalsingletons += 1
			continue
		totaldiscordantly += FR_discordant(read)
	samfile.close()
	return totalreads,totalbases,totaldup,totalmapped,totalproper,totalsingletons,totalmapq5,totalmapq20,mulhits,uniqhits,totaldiscordantly

def mapping_stat(bamfile):
	unmapped = 0
	mapped   = 0
	singletons = 0
	paired  = 0
	paired_mapped = 0
	porper_paired = 0
	dup      = 0
	mapq5   = 0
	mapq20  = 0
	total_reads = 0
	samfile = pysam.Samfile( bamfile, "rb" )
	for read in samfile:
		if read.is_secondary:continue
		total_reads += 1
		if read.is_duplicate:dup += 1
		if read.is_unmapped:
			unmapped += 1
		else:
			mapped += 1
			if read.is_paired:
				paired += 1
				if read.is_proper_pair:
					porper_paired += 1
			if read.mate_is_unmapped:
				singletons += 1
			else:
				paired_mapped += 1
			if read.mapq >=20:
				mapq20 += 1
				mapq5 += 1
			elif read.mapq >=5:
				mapq5 += 1
	samfile.close()
	#print "mapped,unmapped,paired,paired_mapped,porper_paired,singletons,mapq5,mapq20,dup,unmapped"
	#print mapped,unmapped,paired,paired_mapped,porper_paired,singletons,mapq5,mapq20,dup,unmapped
	return total_reads,mapped,unmapped,paired,paired_mapped,porper_paired,singletons,mapq5,mapq20,dup
def unmap(bamfile):
	samfile = pysam.Samfile( bamfile, "rb" )
	tmp = 0
	for read in samfile:
		if read.is_unmapped:
			tmp += 1
	samfile.close()
	#print tmp
	return tmp



def getBeD(bamfile,region=None):
	samfile = pysam.Samfile( bamfile, "rb" )
	if region == None:
		it = samfile.fetch()
	else:
		it = samfile.fetch(*region) ### not same as bam2bed use region method, because will be wrong,  Here we use the *[str(chr),int(start),int(end)] 
	# calculate the end position and print out BED
	take = (0, 2, 3) # CIGAR operation (M/match, D/del, N/ref_skip)
	for read in it:
		if read.is_unmapped: continue
		# compute total length on reference
		t = sum([ l for op,l in read.cigar if op in take ])
		if read.is_reverse: strand = "-"
		else: strand = "+"
		##  rname is chrom name ,  qname is read name 
		yield [samfile.getrname( read.rname ),read.pos,read.pos+t,read.qname,read.mapq,strand]
	del it
	samfile.close()

def map_unmap(bamfile):
	samfile = pysam.Samfile( bamfile, "rb" )
	mapped = samfile.mapped
	unmapped = samfile.unmapped
	samfile.close()
	return mapped,unmapped

"""
11 # 文件中的坐标被认为是1-base的
12 # fetch 时， 输入的坐标为 0-based ，左闭右开。 此时，fetch(chrom,10,14)取的实际位置即为 [11 ~ 14]
"""
def tabixIO(db,seq_col=0,start_col=3,end_col=4):
	ftbi = None
	try:
		ftbi = pysam.Tabixfile(db)
	except Exception,e:
		sys.stderr.write("[WARN] %s\n"%e)
		if os.path.isfile(db):
			sys.stderr.write("[WARN] can not find the tabix for file '%s', auto try to build, please wait ...\n"%db)
		else: 
			sys.stderr.write("[WARN] can not find the tabix for file '%s', auto try to find gz file, please wait ...\n"%db)
		try:
			ftbi = pysam.Tabixfile(db+".gz")
		except Exception,e:
			sys.stderr.write("[INFO] search for 'gz' file, please wait ...\n")
			try:
				pysam.tabix_index(db,seq_col=seq_col,start_col=start_col,end_col=end_col)
				ftbi = pysam.Tabixfile(db+".gz")
			except Exception,e:
			#if not ftbi:
				sys.stderr.write("[ERROR] %s\n"%e)
				sys.stderr.write("[ERROR] '%s' index failed, please Check!\n"%db)
				exit(1)
	if ftbi:
		sys.stderr.write("[INFO] tab index file read done!\n")
	return ftbi

def gtfgffdb(db):
	ftbi = tabixIO(db,seq_col=0,start_col=3,end_col=4)
	return ftbi

if __name__ == "__main__":
	bamfile = sys.argv[1]
	samfile = pysam.Samfile( bamfile, "rb" )	
	count = 0
	for alignread in samfile:
		print alignread.blocks
		count += 1
		if count == 10:
			break
	samfile.close()

