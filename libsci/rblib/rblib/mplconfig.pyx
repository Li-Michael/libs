# -*- coding: UTF-8 -*-
import sys
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib as mpl
import matplotlib.cm as cm
from matplotlib import cycler
import itertools

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
mpl.rcParams['axes.prop_cycle'] = cycler(u"color",[u'#E24A33', u'#348ABD', u'#988ED5', u'#777777', u'#FBC15E', u'#8EBA42', u'#FFB5B8'])
#mpl.rcParams['axes.facecolor'] = u"#FFFFF0" #axes.facecolor
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
mpl.rcParams['axes.labelcolor'] = u'#000000'
#mpl.rcParams['xtick.color'] = u'#000000'
#mpl.rcParams['ytick.color'] = u'#000000'
mpl.rcParams['axes.edgecolor'] = u'#000000'
mpl.rcParams['text.color'] = u'#000000'

mpl.rcParams['axes.grid'] = False
#mpl.rcParams['font.fantasy'] = [u'Comic Sans MS', u'Chicago', u'Charcoal', u'ImpactWestern', u'fantasy']
#mpl.rcParams['font.cursive'] = [u'Apple Chancery', u'Textile', u'Zapf Chancery', u'Sand', u'cursive']
mpl.rcParams['font.sans-serif'] = [u'Arial',u'Helvetica',u'Bitstream Vera Sans', u'DejaVu Sans', u'Lucida Grande', u'Verdana', u'Geneva', u'Lucid', u'Arial',u'Helvetica', u'Avant Garde', u'sans-serif']
mpl.rcParams['font.serif'] = [u'Times', u'Palatino', u'New Century Schoolbook', u'Bookman', u'Computer Modern Roman'] 
mpl.rcParams['font.weight'] = 'normal'
#mpl.rcParams['font.monospace'] = [u'Bitstream Vera Sans Mono', u'DejaVu Sans Mono', u'Andale Mono', u'Nimbus Mono L', u'Courier New', u'Courier',u'Fixed', u'Terminal', u'monospace']
mpl.rcParams['savefig.edgecolor'] = 'w' 
mpl.rcParams['font.size'] = 12
mpl.rcParams['legend.fontsize'] = 12
mpl.rcParams['font.stretch'] = 'normal'
mpl.rcParams['font.family'] = [u'sans-serif',u'serif']
mpl.rcParams['xtick.direction'] = "out"
mpl.rcParams['ytick.direction'] = "out"
###
from matplotlib.patches import Polygon
# to get kmeans and scipy.cluster.hierarchy
from scipy.cluster.vq import *
from scipy.cluster.hierarchy import *

###
from matplotlib.colors import LogNorm

##kmeans归一化处理 from scipy.cluster.vq import whiten
from scipy.cluster.vq import whiten


#color define 
colordefine = {
		"bmh": [u'#348ABD', u'#A60628', u'#7A68A6', u'#467821', u'#D55E00', u'#CC79A7', u'#56B4E9', u'#009E73', u'#F0E442'],
		"ggplot1": [u'#E41A1C', u'#377EB8', u'#4DAF4A', u'#984EA3', u'#FF7F00', u'#FFFF33', u'#A65628', u'#F781BF', u'#999999'], 
		"ggplot2": ["#66C2A5", "#FC8D62","#8DA0CB","#E78AC3","#A6D854","#FFD92F","#E5C494","#B3B3B3"],
		"ggplot3": ["#FF6C91","#BC9D00","#00BB57","#00B8E5","#CD79FF"],
		"tableau10M": ["#609DCA","#FF9641","#38C25D","#FF5B4E","#B887C3","#B67365","#FE90C2","#A4A09B","#D2CC5A"],
		"tableau10": ["#0076AE","#FF7400","#00A13B","#EF0000","#9E63B5","#985247","#F66EB8","#7F7C77","#C2BD2C"],
		"seaborn": ["#4C72B0","#55A868","#C44E52","#8172B2","#CCB974","#64B5CD"],
		"seabornHSUL": ["#F67088","#CE8F31","#96A331","#32B165", "#35ACA4", "#38A7D0", "#A38CF4","#F461DD"],
		"D3": ["#5E9CC6","#FF7D0B", "#2CA02C", "#D62728", "#9467BD","#8C564B"],
		}
colorCMs = "Accent, Accent_r, Blues, Blues_r, BrBG, BrBG_r, BuGn, BuGn_r, BuPu, BuPu_r, CMRmap, CMRmap_r, Dark2, Dark2_r, GnBu, GnBu_r, Greens, Greens_r, Greys, Greys_r, OrRd, OrRd_r, Oranges, Oranges_r, PRGn, PRGn_r, Paired, Paired_r, Pastel1, Pastel1_r, Pastel2, Pastel2_r, PiYG, PiYG_r, PuBu, PuBuGn, PuBuGn_r, PuBu_r, PuOr, PuOr_r, PuRd, PuRd_r, Purples, Purples_r, RdBu, RdBu_r, RdGy, RdGy_r, RdPu, RdPu_r, RdYlBu, RdYlBu_r, RdYlGn, RdYlGn_r, Reds, Reds_r, Set1, Set1_r, Set2, Set2_r, Set3, Set3_r, Spectral, Spectral_r, Wistia, Wistia_r, YlGn, YlGnBu, YlGnBu_r, YlGn_r, YlOrBr, YlOrBr_r, YlOrRd, YlOrRd_r, afmhot, afmhot_r, autumn, autumn_r, binary, binary_r, bone, bone_r, brg, brg_r, bwr, bwr_r, cool, cool_r, coolwarm, coolwarm_r, copper, copper_r, cubehelix, cubehelix_r, flag, flag_r, gist_earth, gist_earth_r, gist_gray, gist_gray_r, gist_heat, gist_heat_r, gist_ncar, gist_ncar_r, gist_rainbow, gist_rainbow_r, gist_stern, gist_stern_r, gist_yarg, gist_yarg_r, gnuplot, gnuplot2, gnuplot2_r, gnuplot_r, gray, gray_r, hot, hot_r, hsv, hsv_r, inferno, inferno_r, jet, jet_r, magma, magma_r, nipy_spectral, nipy_spectral_r, ocean, ocean_r, pink, pink_r, plasma, plasma_r, prism, prism_r, rainbow, rainbow_r, seismic, seismic_r, spring, spring_r, summer, summer_r, tab10, tab10_r, tab20, tab20_r, tab20b, tab20b_r, tab20c, tab20c_r, terrain, terrain_r, viridis, viridis_r, winter, winter_r".split(", ")

def __getallcolors():
	keys = []
	for key in colordefine.keys() + colorCMs:
		#if key.endswith("_r"):continue
		keys.append(key)
	return keys

def styles(num,colorgrad=None,defaultnum = 8):
	if colorgrad == None:colorgrad = "Dark2"
	elif not isinstance(colorgrad,str):
		try:
			colorgrad = colorgrad.name
		except:
			sys.stderr.write("[ERROR] unkown colorgrad name\n")
			exit(1)
	if colorgrad in colordefine:
		axescolors = colordefine[colorgrad]
	elif colorgrad in colorCMs:
		stylecolors = color_grad(max(num,defaultnum),colorgrad=colorgrad)
		axescolors = map(matplotlib.colors.rgb2hex,stylecolors)
	else:
		sys.stderr.write("[ERROR] unkown colorgrad name\n")
		exit(1)
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


def inscolor(stringlist,colorgrad = "Dark2"):
	ret_color,ret_lines,ret_marker = styles(len(stringlist),colorgrad = colorgrad)
	h = {}
	for i in xrange(len(stringlist)):
		h[stringlist[i]] = ret_color[i]
	return h

## this is not same as sequential colormaps 
def color_grad(num,colorgrad="Dark2"):
	cminstance = cm.get_cmap(colorgrad)
	color_class = cminstance(np.linspace(0, 1, num))
	return color_class


def rgb2hex(rgbORrgba):
	return matplotlib.colors.rgb2hex(rgbORrgba)

if __name__ == "__main__":
	print color_grad(3)

"""
113     #   plot(x, y, color='green', linestyle='dashed', marker='o',
114     #                    markerfacecolor='blue', markersize=12).
115     # 因此，产生3个元素列表，for  colorstyle， linestyle， makerstyle  ##
116     #1247 'b'         blue
117     #1248 'g'         green
118     #1249 'r'         red
119     #1250 'c'         cyan
120     #1251 'm'         magenta
121     #1252 'y'         yellow
122     #1253 'k'         black
123     #1271     ================    ===============================
124     #1272     character           description
125     #1273     ================    ===============================
126     #1274     ``'-'``             solid line style
127     #1275     ``'--'``            dashed line style
128     #1276     ``'-.'``            dash-dot line style
129     #1277     ``':'``             dotted line style
130     #1278     
131     #1279     
132     #1280     ``'.'``             point marker
133     #1281     ``','``             pixel marker
134     #1282     ``'o'``             circle marker
135     #1283     ``'v'``             triangle_down marker
136     #1284     ``'^'``             triangle_up marker
137     #1285     ``'<'``             triangle_left marker
138     #1286     ``'>'``             triangle_right marker
139     #1287     ``'1'``             tri_down marker
140     #1288     ``'2'``             tri_up marker
141     #1289     ``'3'``             tri_left marker
142     #1290     ``'4'``             tri_right marker
143     #1291     ``'s'``             square marker
144     #1292     ``'p'``             pentagon marker
145     #1293     ``'*'``             star marker
146     #1294     ``'h'``             hexagon1 marker
147     #1295     ``'H'``             hexagon2 marker
148     #1296     ``'+'``             plus marker
149     #1297     ``'x'``             x marker
150     #1298     ``'D'``             diamond marker
151     #1299     ``'d'``             thin_diamond marker
152     #1300     ``'|'``             vline marker
153     #1301     ``'_'``             hline marker
154     #1302 
155     #1303 marker: [ ``7`` | ``4`` | ``5`` | ``6`` | ``'o'`` | ``'D'`` | ``'h'`` | ``'H'`` | ``'_'`` | ``''`` | ``'None'`` | ``' '`` | ``None`` |        ``'8'`` | ``'p'``      | ``','`` | ``'+'`` | ``'.'`` | ``'s'`` | ``'*'`` | ``'d'`` | ``3`` | ``0`` | ``1`` | ``2`` | ``'1'`` | ``'3'`` | ``'4'`` |      ``'2'`` | ``'v'`` | ``'<'``       | ``'>'`` | ``'^'`` | ``'|'`` | ``'x'`` | ``'$...$'`` | *tuple* | *Nx2 array* ]
"""

