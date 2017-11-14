import sys
import numpy as np
from rblib import cluster
import pandas as pd
import h5py
# power call # default use 6, + or - need to be consider
# Often choosing beta=6 works well but in general we use the “scale free topology criterion” described in Zhang and Horvath 2005.

class SFnet(object):
	def __init__(self,Xcorr,anno,power=6,signtype=0,minsize=30,threads=4,ncluster=50,hdfprefix="save_data"):
		self.Xcorr = Xcorr.copy()
		self.power = power
		self.signtype = signtype
		self.adjacency = None
		self.connectivity = None
		self.subconnectivity = None
		self.disstom = None
		self.modules = None
		self.anno = anno
		self.minsize = minsize
		self.threads = threads
		self.ncluster = 50
		self.hdfname = hdfprefix + ".hdf"
		self.fhdf = None
	def rwdata(self,mode="r"):
		self.fhdf = h5py.File(self.hdfname,mode)
		return 0
	def savedata(self,data,dataname):
		self.fhdf.create_dataset(dataname, data = data)
		return 0
	def closedata(self):
		self.fhdf.close()
		return 0
	def power_adjacency(self):
		if self.signtype == 0:
			self.Xcorr = np.abs(self.Xcorr)
		elif self.signtype == 1:
			self.Xcorr = (1+self.Xcorr) / 2.0
		elif self.signtype == 2:
			self.Xcorr[self.Xcorr< 0] = 0
		self.adjacency = self.Xcorr ** self.power
		return 0
	def callconnectivity(self):
		self.connectivity = np.sum(self.adjacency,axis=0) - 1 # to Minus itself
		return 0
	def dissTOM(self):
		Xadj = self.adjacency.copy()
		n,p = Xadj.shape
		for i in xrange(n):
			Xadj[i,i] = 0
		Tom = np.dot(Xadj,Xadj)
		for i in xrange(n):
			atmp = Xadj[i,:]
			tmpmink = np.minimum(self.connectivity,self.connectivity[i])
			Tom[i,:] = (Tom[i,:] + atmp)/(tmpmink+1-atmp)
			Tom[i,i] = 1
		del Xadj
		self.disstom = 1-Tom # topological overlap dissimilarity 
		return 0
	def clustermodule(self):
		disstomcluster = cluster.Cluster(Xdist=self.disstom,threads=self.threads,ncluster=self.ncluster)
		clusterlabels = disstomcluster.hcluster()
		clusternames = set(clusterlabels.tolist())
		self.modules = np.asarray(["Unknown",]*len(self.anno))
		self.subconnectivity = np.zeros(len(self.anno))
		for name in clusternames:
			idx = clusterlabels == name
			if np.sum(idx) < self.minsize:
				name = "others"
			name = str(name)
			self.modules[idx] = name 
			tmpXadj = self.adjacency[idx,idx]
			self.subconnectivity[idx] = np.sum(tmpXadj,axis=0) - 1
		
		return 0
	"""
	def callintra_connectivity(self):
		clusternames = set(self.clusteridx)
		self.subconnectivity = np.zeros(len(self.anno))
		self.modules = np.zeros(len(self.anno))
		for i in xrange(len(clusternames)):
			name = clusternames[i]
			idx = self.clusteridx == name
			if np.sum(idx) < self.minsize:
				name = "others"
			name = str(name)
			self.modules[idx] = name	
			tmpXadj = self.adjacency[idx,idx]
			self.subconnectivity[idx] = np.sum(tmpXadj,axis=0) - 1
		return 0
	"""
	def outputmodule(self,pvalues,fileout="sfnet.out"):
		# print connectivity
		f1 = file(fileout + ".nodes.tsv","w")
		f2 = file(fileout + ".edges.tsv","w")
		f1.write("#Gene\tModule_id\tInModule.connectivity\tOverall.connectivity\n")
		f2.write("#Gene1\tGene2\tcorr\tpvalue\tadjacency\n")
		p = len(self.anno)
		for i in xrange(p):
			name = self.anno[i]
			f1.write("%s\t%s\t%s\t%s\n"%(name,self.modules[i],self.subconnectivity[i],self.connectivity[i]))
		f1.close()

		for i in xrange(p-1):
			for j in xrange(i+1,p):
				tmpadj = self.adjacency[i,j]
				f2.write("%s\t%s\t%.7f\t%.3e\t%.7f\n"%(self.anno[i],self.anno[j],self.Xcorr[i,j],pvalues[i,j],tmpadj))
		return 0	



