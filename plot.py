import math
import numpy as np
from matplotlib import pyplot as plt

data = np.array([
    [1, 9],
    [20001, 5186],
    [40001, 9018],
    [60001, 11728],
    [80001, 13381],
    [100001, 14995],
    [120001, 16334],
    [140001, 17986],
    [160001, 20648],
    [180001, 23574],
    [200001, 26474],
    [220001, 29331],
    [240001, 31992],
    [260001, 34573],
    [280001, 38001],
    [300001, 40483],
    [320001, 43493],
    [340001, 46872],
    [360001, 50206],
    [380001, 52643],
    [400001, 55786],
    [420001, 58849],
    [440001, 61967],
    [460001, 66393],
    [480001, 67293],
    [500001, 70557],
    [520001, 72660],
    [540001, 76711],
    [560001, 79913],
    [580001, 81873],
    [600001, 86514],
    [620001, 88309],
    [640001, 91938],
    [660001, 94849],
    [680001, 97884],
    [700001, 101425],
    [720001, 104050],
    [740001, 107733],
    [760001, 111087],
    [780001, 113683],
    [800001, 116939],
    [820001, 120627],
    [840001, 123466],
    [860001, 126483],
    [880001, 129502],
    [900001, 132035],
    [920001, 134882],
    [940001, 138171],
    [960001, 141140],
    [980001, 144656],
    [1000001, 146899],
    [1020001, 149465],
    [1040001, 152426],
    [1060001, 155650],
    [1080001, 159483],
    [1100001, 163683],
    [1120001, 166165],
    [1140001, 169160],
    [1160001, 171670],
    [1180001, 174784],
    [1200001, 178258],
    [1220001, 182316],
    [1240001, 184806],
    [1260001, 188437],
    [1280001, 191470],
    [1300001, 194352],
    [1320001, 198227],
    [1340001, 202042],
    [1360001, 205319],
    [1380001, 209148],
    [1400001, 212511],
    [1420001, 216671],
    [1440001, 218609],
    [1460001, 222229],
    [1480001, 225654],
    [1500001, 229291],
    [1520001, 232936],
    [1540001, 234906],
    [1560001, 237923],
    [1580001, 241803],
    [1600001, 246054],
    [1620001, 248726],
    [1640001, 252820],
    [1660001, 255783],
    [1680001, 259850],
    [1700001, 264765],
    [1720001, 264828],
    [1740001, 268202],
    [1760001, 272250],
    [1780001, 275175],
    [1800001, 281112],
    [1820001, 280278],
    [1840001, 284974],
    [1860001, 287533],
    [1880001, 290266],
    [1900001, 294106],
    [1920001, 296253],
    [1940001, 299027],
    [1960001, 302031],
    [1980001, 304375],
    [2000001, 308109],
    [2020001, 310483],
    [2040001, 316505],
    [2060001, 316580],
    [2080001, 320961],
    [2100001, 325669],
    [2120001, 330963],
    [2140001, 332100],
    [2160001, 335604],
    [2180001, 341551],
    [2200001, 345432],
    [2220001, 346090],
    [2240001, 348420],
    [2260001, 352208],
    [2280001, 357365],
    [2300001, 361257],
    [2320001, 363073],
    [2340001, 368249],
    [2360001, 367306],
    [2380001, 371334],
    [2400001, 375150],
    [2420001, 378312],
    [2440001, 381392],
    [2460001, 385328],
    [2480001, 388314],
    [2500001, 397440],
    [2520001, 398335],
    [2540001, 401051],
    [2560001, 402062],
    [2580001, 405435],
    [2600001, 410677],
    [2620001, 411823],
    [2640001, 422823],
    [2660001, 420934],
    [2680001, 429011],
    [2700001, 428772],
    [2720001, 435423],
    [2740001, 438680],
    [2760001, 441987],
    [2780001, 444969],
    [2800001, 449868],
    [2820001, 454686],
    [2840001, 458462],
    [2860001, 460248],
    [2880001, 462187],
    [2900001, 461378],
    [2920001, 469434],
    [2940001, 474217],
    [2960001, 476576],
    [2980001, 478596],
    [3000001, 484086],
    [3020001, 486083],
    [3040001, 485946],
    [3060001, 488574],
    [3080001, 493081],
    [3100001, 497754],
    [3120001, 498701],
    [3140001, 503037],
    [3160001, 508397],
    [3180001, 510645],
    [3200001, 514269],
    [3220001, 517154],
    [3240001, 522462],
    [3260001, 525175],
    [3280001, 528770],
    [3300001, 531414],
    [3320001, 535198],
    [3340001, 539680],
    [3360001, 543404],
    [3380001, 546449],
    [3400001, 548403],
    [3420001, 570172],
    [3440001, 576424],
    [3460001, 583549],
    [3480001, 587081],
    [3500001, 585787],
    [3520001, 592436],
    [3540001, 582459],
    [3560001, 584353],
    [3580001, 590222],
    [3600001, 599240],
    [3620001, 602257],
    [3640001, 601705],
    [3660001, 596280],
    [3680001, 596443],
    [3700001, 605427],
    [3720001, 608549],
    [3740001, 614245],
    [3760001, 635911],
    [3780001, 628254],
    [3800001, 633982],
    [3820001, 637334],
    [3840001, 638290],
    [3860001, 646347],
    [3880001, 632188],
    [3900001, 652319],
    [3920001, 643340],
    [3940001, 640448],
    [3960001, 648111],
    [3980001, 656621],
])

data_nlogn = np.array([[n, n * math.log2(n) * 0.0075] for n in data.T[0]])

x, y = data.T
plt.scatter(x, y, marker="+", s=25, linewidths=1)
x, y = data_nlogn.T
plt.scatter(x, y, marker=".", s=5)
plt.show()
