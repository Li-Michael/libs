#!/usr/bin/env python
import sys
from optparse import OptionParser,OptionGroup
import seqprocess
import time
import bamio
# exon quant 
# gene quant 
# transcript quant
# so we can use exon to get counts , then to get transcript , to get gene 

def __main():
	start_time = time.time()
	usage = "usage: %prog [options] Annotation_file [S1.bam,[S2.bam, ...]]"
	description = "Contact: Rong Zhengqin <rongzhengqin@honortech.cn>"
	parser = OptionParser(usage,version="%prog 0.1",description = description)
	Common_group = OptionGroup(parser,'Required Options')

	Extend_group = OptionGroup(parser,'Extend Options')
	Common_group.add_option('-t',dest='annotype',help="annotation file format [default=gtf],'gff,gtf,bed,refgene,mycustom,'",metavar='STR',type='choice',choices=["gtf","gff","refgene","bed","mycustom"],default='gtf')
	Common_group.add_option('--gattr',dest='gattr',help="gene attr keyword [gene_name]",metavar="STR",type="string",default="gene_name")
	Common_group.add_option('--tattr',dest='tattr',help='transcript attr keyword [oId]',metavar='STR',type="string",default="oId")
	Common_group.add_option('--gidattr',dest='gidattr',help="gene id attr keyword [gene_id]",metavar="STR",type="string",default="gene_id")
	Common_group.add_option('--tidattr',dest='tidattr',help="transcript id attr keyword [transcript_id]",metavar="STR",type="string",default="transcript_id")
	Common_group.add_option('--biotypeattr',dest='biotypeattr',help="biotype id attr keyword [bio_type]",metavar="STR",type="string",default="bio_type")
	Common_group.add_option('--csanno',dest='csanno',help='codon start annotype keyword [CDS]',metavar='STR',type='string',default='CDS')
	Common_group.add_option('--ceanno',dest='ceanno',help='codon stop annotype keyword [CDS]',metavar='STR',type='string',default='CDS')
	#Common_group.add_option('--region',dest="region",help="plot region,like: 'chr1:101:172', region < 10Mb",metavar='STR',type='string',default=None)


	annoregion = seqprocess.Annoregion(fmt=options.annotype,gattr=options.gattr,tattr=options.tattr,csanno=options.csanno,ceanno=options.ceanno,gidattr=options.gidattr,tidattr=options.tidattr,biotypeattr=options.biotypeattr,tanno=options.plotanno)



