import sys
import h5py
import pandas as pd
import numpy as np
pvalues = np.random.random(10)
corr    = np.random.random(10)
data = pd.DataFrame({
	"i":1,
	"pvalues":pvalues,
	"corr":corr,
	})
data.to_hdf('foo.h5','data')
print h5py.File.__doc__

#print pd.read_hdf('foo.h5','data')

a = np.random.random((5,3))
datafile = h5py.File('tmpdata.hdf','a')
if "a" in datafile:
	del datafile['a']
datafile.create_dataset('a', data=a)

print datafile["a"][[1,2]][:,[1,2]]
print np.sum(datafile["a"],axis=0)
print datafile["a"].shape

b = np.random.random((3,5))
aa = datafile["a"][:]
print np.dot(datafile["a"],b)
print np.dot(aa,b)
print datafile['a']
print np.minimum(datafile['a'][0],datafile['a'][0,0])
print datafile['a'][0,0]
idx1 = np.asarray([True,True,False,False,False])
print idx1
dd =  datafile['a']
#print datafile['a'][idx1]
idxx = np.where(idx1==True)
idxx = idxx[0].tolist()
print dd[idxx]
dd2 = datafile['a'][:]
print dd2[idx1]
datafile.close()

