# -*- coding: UTF-8 -*-
import sys
import numpy as np
import scipy as sp
from scipy import stats
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from  rklib.utils import dirDetectCreate 
import matplotlib as mpl
import matplotlib.gridspec as gridspec
import matplotlib.cm as cm
from matplotlib import font_manager as fm
from matplotlib_venn import venn2,venn3
import itertools
import mutilstats

#print cm._cmapnames
#['Spectral', 'copper', 'RdYlGn', 'Set2', 'summer', 'spring', 'gist_ncar', 'terrain', 'OrRd', 'RdBu', 'autumn', 'gist_earth', 'Set1', 'PuBu', 'Set3', 'brg', 'gnuplot2', 'gist_rainbow', 'pink', 'binary', 'winter', 'jet', 'BuPu', 'Dark2', 'prism', 'Oranges', 'gist_yarg', 'BuGn', 'hot', 'PiYG', 'YlOrBr', 'PRGn', 'Reds', 'spectral', 'bwr', 'RdPu', 'cubehelix', 'Greens', 'rainbow', 'Accent', 'gist_heat', 'YlGnBu', 'RdYlBu', 'Paired', 'flag', 'hsv', 'BrBG', 'seismic', 'Blues', 'Purples', 'cool', 'Pastel2', 'gray', 'coolwarm', 'Pastel1', 'gist_stern', 'gnuplot', 'GnBu', 'YlGn', 'Greys', 'RdGy', 'ocean', 'YlOrRd', 'PuOr', 'PuRd', 'gist_gray', 'CMRmap', 'PuBuGn', 'afmhot', 'bone']

# ggplot axes colors [u'#E24A33', u'#348ABD', u'#988ED5', u'#777777', u'#FBC15E', u'#8EBA42', u'#FFB5B8']

# for projection='3d'
from mpl_toolkits.mplot3d import Axes3D
from scipy.cluster.hierarchy import fcluster; import pandas
mpl.rcParams['grid.alpha'] = 1.0
mpl.rcParams['pgf.texsystem'] = 'xelatex'
mpl.rcParams['pdf.fonttype'] = 42
mpl.rcParams['svg.fonttype'] = 'none'
mpl.rcParams['axes.titleweight'] = 'normal'
mpl.rcParams['axes.labelcolor'] = u'#000000'
mpl.rcParams['text.color'] = 'k'
mpl.rcParams['lines.dash_joinstyle'] = 'round'
mpl.rcParams['text.latex.unicode'] = False
mpl.rcParams['path.simplify_threshold'] = 0.11111111111
mpl.rcParams['ytick.labelsize'] = 'medium'
mpl.rcParams['ps.papersize'] = 'letter'
mpl.rcParams['grid.color'] = 'gray'
mpl.rcParams['axes.color_cycle'] = [u'#E24A33', u'#348ABD', u'#988ED5', u'#777777', u'#FBC15E', u'#8EBA42', u'#FFB5B8']
mpl.rcParams['axes.facecolor'] = u"#FFFFF0" #axes.facecolor
mpl.rcParams['ytick.color'] = u'#000000'
mpl.rcParams['xtick.color'] = u'#000000'
mpl.rcParams['figure.figsize'] = [8.0, 6.0]
#mpl.rcParams['ps.fonttype'] = 3
mpl.rcParams['path.simplify'] = True
mpl.rcParams['toolbar'] = 'toolbar2'
mpl.rcParams['axes.linewidth'] = 0.5
mpl.rcParams['lines.linewidth'] = 0.5
mpl.rcParams['lines.markeredgewidth'] = 0.5
mpl.rcParams['lines.markersize'] = 6
plt.style.use('bmh')
mpl.rcParams['axes.labelcolor'] = u'#000000'
mpl.rcParams['xtick.color'] = u'#000000'
mpl.rcParams['ytick.color'] = u'#000000'
mpl.rcParams['axes.edgecolor'] = u'#000000'
mpl.rcParams['text.color'] = u'#000000'

mpl.rcParams['axes.grid'] = False
mpl.rcParams['font.fantasy'] = [u'Comic Sans MS', u'Chicago', u'Charcoal', u'ImpactWestern', u'fantasy']
mpl.rcParams['font.cursive'] = [u'Apple Chancery', u'Textile', u'Zapf Chancery', u'Sand', u'cursive']
mpl.rcParams['font.sans-serif'] = [u'Arial',u'Helvetica',u'Bitstream Vera Sans', u'DejaVu Sans', u'Lucida Grande', u'Verdana', u'Geneva', u'Lucid', u'Arial',u'Helvetica', u'Avant Garde', u'sans-serif']
mpl.rcParams['font.serif'] = [u'Times', u'Palatino', u'New Century Schoolbook', u'Bookman', u'Computer Modern Roman'] 
mpl.rcParams['font.weight'] = 'normal'
#mpl.rcParams['font.monospace'] = [u'Bitstream Vera Sans Mono', u'DejaVu Sans Mono', u'Andale Mono', u'Nimbus Mono L', u'Courier New', u'Courier',u'Fixed', u'Terminal', u'monospace']
mpl.rcParams['savefig.edgecolor'] = 'w' 
mpl.rcParams['font.size'] = 12
mpl.rcParams['legend.fontsize'] = 12
mpl.rcParams['font.stretch'] = 'normal'
#mpl.rcParams['font.family'] = [u'sans-serif',]
#mpl.rcParams['font.family'] = 'Arial'
#mpl.rcParams['font.sans-serif'].insert(0, 'Liberation Sans')
mpl.rcParams['font.family'] = [u'sans-serif',u'serif']

###
from matplotlib.patches import Polygon
# to get kmeans and scipy.cluster.hierarchy
from scipy.cluster.vq import *
from scipy.cluster.hierarchy import *

###
from matplotlib.colors import LogNorm

##kmeans归一化处理 from scipy.cluster.vq import whiten
from scipy.cluster.vq import whiten
#mpl.style.use('ggplot')

def styles(num,colorgrad=None):
	#	plot(x, y, color='green', linestyle='dashed', marker='o',
	#			         markerfacecolor='blue', markersize=12).
	# 因此，产生3个元素列表，for  colorstyle， linestyle， makerstyle  ##
	#1247 'b'         blue
	#1248 'g'         green
	#1249 'r'         red
	#1250 'c'         cyan
	#1251 'm'         magenta
	#1252 'y'         yellow
	#1253 'k'         black
	#1271     ================    ===============================
	#1272     character           description
	#1273     ================    ===============================
	#1274     ``'-'``             solid line style
	#1275     ``'--'``            dashed line style
	#1276     ``'-.'``            dash-dot line style
	#1277     ``':'``             dotted line style
	#1278     
	#1279     
	#1280     ``'.'``             point marker
	#1281     ``','``             pixel marker
	#1282     ``'o'``             circle marker
	#1283     ``'v'``             triangle_down marker
	#1284     ``'^'``             triangle_up marker
	#1285     ``'<'``             triangle_left marker
	#1286     ``'>'``             triangle_right marker
	#1287     ``'1'``             tri_down marker
	#1288     ``'2'``             tri_up marker
	#1289     ``'3'``             tri_left marker
	#1290     ``'4'``             tri_right marker
	#1291     ``'s'``             square marker
	#1292     ``'p'``             pentagon marker
	#1293     ``'*'``             star marker
	#1294     ``'h'``             hexagon1 marker
	#1295     ``'H'``             hexagon2 marker
	#1296     ``'+'``             plus marker
	#1297     ``'x'``             x marker
	#1298     ``'D'``             diamond marker
	#1299     ``'d'``             thin_diamond marker
	#1300     ``'|'``             vline marker
	#1301     ``'_'``             hline marker
	#1302 
	#1303 marker: [ ``7`` | ``4`` | ``5`` | ``6`` | ``'o'`` | ``'D'`` | ``'h'`` | ``'H'`` | ``'_'`` | ``''`` | ``'None'`` | ``' '`` | ``None`` | ``'8'`` | ``'p'``      | ``','`` | ``'+'`` | ``'.'`` | ``'s'`` | ``'*'`` | ``'d'`` | ``3`` | ``0`` | ``1`` | ``2`` | ``'1'`` | ``'3'`` | ``'4'`` | ``'2'`` | ``'v'`` | ``'<'``       | ``'>'`` | ``'^'`` | ``'|'`` | ``'x'`` | ``'$...$'`` | *tuple* | *Nx2 array* ]
	
	#color_raw = itertools.cycle(itertools.chain(['b','r','g','c','m','y','k']))
	if colorgrad == None:colorgrad = cm.Dark2
	stylecolors = color_grad(num,colorgrad=colorgrad)
	#axescolors = [u'#E24A33', u'#348ABD', u'#988ED5', u'#777777', u'#FBC15E', u'#8EBA42', u'#FFB5B8']
	#color_raw = itertools.cycle(itertools.chain(plt.rcParams['axes.color_cycle']))
	axescolors = map(matplotlib.colors.rgb2hex,stylecolors)
	if colorgrad == None and num <=9:
		#axescolors = [u'#E24A33', u'#348ABD', u'#988ED5', u'#777777', u'#FBC15E', u'#8EBA42', u'#FFB5B8']
		axescolors = [u'#0076AE',u'#FF7400',u'#00A13B',u'#EF0000',u'#9E63B5',u'#985247',u'#F66EB8',u'#7F7C77',u'#C2BD2C']
		#axescolors = [u'#66C2A5', u'#FC8D62',u'#8DA0CB',u'#E78AC3',u'#A6D854',u'#FFD92F',u'#E5C494',u'#B3B3B3']
	color_raw = itertools.cycle(itertools.chain(axescolors))
	lines_raw = itertools.cycle(itertools.chain(['-','--','-.',':']))
	marker_raw = itertools.cycle(itertools.chain(['o','^','s','+','*','D','v','1','2','x','3','4','s','p','>','<','h','d','H']))
	ret_color = []
	ret_lines = []
	ret_marker = []
	for i in xrange(num):
		ret_color.append(color_raw.next())
		ret_lines.append(lines_raw.next())
		ret_marker.append(marker_raw.next())
	return ret_color,ret_lines,ret_marker

"""
15 ## [u'#348ABD', u'#A60628', u'#7A68A6', u'#467821', u'#D55E00', u'#CC79A7', u'#56B4E9', u'#009E73', u'#F0E442', u'#0072B2'] ## bmh
 16 ## [u'#E41A1C', u'#377EB8', u'#4DAF4A', u'#984EA3', u'#FF7F00', u'#FFFF33', u'#A65628', u'#F781BF', u'#999999']  ## ggplot set 1
  17 ## [66C2A5, FC8D62,8DA0CB,E78AC3,A6D854,FFD92F,E5C494,B3B3B3]ggplot set 2
   18 ## [FF6C91,BC9D00,00BB57,00B8E5,CD79FF]ggplot set 3
    19 ## [609DCA,FF9641,38C25D,FF5B4E,B887C3,B67365,FE90C2,A4A09B,D2CC5A,] tableau 10 medium
	 20 ## [0076AE,FF7400,00A13B,EF0000,9E63B5,985247,F66EB8,7F7C77,C2BD2C,] tableau 10
	  21 ## [4C72B0,55A868,C44E52,8172B2,CCB974,64B5CD] seaborn 
	   22 ## [F67088,CE8F31,96A331,32B165, 35ACA4, 38A7D0, A38CF4,F461DD] seaborn hsul
	    23 ## [5E9CC6,FF7D0B, 2CA02C, D62728, 9467BD, 8C564B] D3.js

"""

def inscolor(stringlist,colorgrad = cm.Dark2):
	ret_color,ret_lines,ret_marker = styles(len(stringlist),colorgrad = colorgrad)
	h = {}
	for i in xrange(len(stringlist)):
		h[stringlist[i]] = ret_color[i]
	return h

## this is not same as sequential colormaps 
def color_grad(num,colorgrad=cm.Dark2):
	color_class = colorgrad(np.linspace(0, 1, num))
	return color_class


def rgb2hex(rgbORrgba):
	return matplotlib.colors.rgb2hex(rgbORrgba)

if __name__ == "__main__":
	print color_grad(3)


