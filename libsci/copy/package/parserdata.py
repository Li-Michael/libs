import sys
from rblib.mutilstats import Pdsampleinfo,Pdmatrix
import numpy as np
def readsninfo(sampleinfo,phenotype="category"):
	sinfo = Pdsampleinfo()
	ret = sinfo.parse_sampleinfo(sampleinfo,phenotype=phenotype)
	#print sinfo.df
	if ret: return None
	else: return sinfo

def readmatrix(matrixfile,):
	data = Pdmatrix()
	ret = data.parse_matrix_anno(matrixfile,cutoff=-np.inf,precent=0.0,addtolog=0.000,log2tr=0,missvalue=np.nan)
	if ret: return None
	else:
		return data

## study method
def plotpower():
	rho = np.linspace(0,1,41)
	rho1 = rho ** 1
	rho2 = rho ** 2
	rho3 = rho ** 4
	rho4 = rho ** 6
	rho5 = rho ** 8
	rho6 = rho.copy()
	rho6[rho >= 0.8] = 1.0
	rho6[rho < 0.8]  = 0.0
	print "#rho\tpower=1\tpower=2\tpower=4\tpower=6\tpower=8\tsgn=0.8"
	for i in xrange(len(rho)):
		print "\t".join(map(str,[rho[i],rho1[i],rho2[i],rho3[i],rho4[i],rho5[i],rho6[i]]))
	return 0


from rblib.corr_dist import nancorrmatrix_self,nancorrmatrix_self_mp
from rblib.sfnet import SFnet
import time



if __name__ == "__main__":
	sinfo = readsninfo(sys.argv[1])
	data = readmatrix(sys.argv[2])
	t0 = time.time()
	corr1,pval1 = nancorrmatrix_self_mp(data.df.values,nprocessor=8)
	sfnet = SFnet(corr1,data.anno,power=6,signtype=0,minsize=30,threads=4)
	sfnet.power_adjacency()
	sfnet.callconnectivity()
	sfnet.dissTOM()
	sfnet.clustermodule()
	sfnet.outputmodule(pval1)
	print time.time()-t0
	exit(0)	
