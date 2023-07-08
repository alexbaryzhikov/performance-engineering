import numpy as np
from matplotlib import pyplot as plt

data = np.array([
    [1, 8],
    [20001, 4133],
    [40001, 7826],
    [60001, 10453],
    [80001, 12418],
    [100001, 13989],
    [120001, 15372],
    [140001, 17307],
    [160001, 19758],
    [180001, 22762],
    [200001, 25438],
    [220001, 27997],
    [240001, 31134],
    [260001, 33115],
    [280001, 36444],
    [300001, 39227],
    [320001, 42245],
    [340001, 45384],
    [360001, 47092],
    [380001, 50412],
    [400001, 53715],
    [420001, 57069],
    [440001, 60222],
    [460001, 62077],
    [480001, 64999],
    [500001, 67700],
    [520001, 70619],
    [540001, 74567],
    [560001, 77294],
    [580001, 79692],
    [600001, 83675],
    [620001, 86276],
    [640001, 89493],
    [660001, 91791],
    [680001, 95390],
    [700001, 97305],
    [720001, 100143],
    [740001, 104685],
    [760001, 107778],
    [780001, 109369],
    [800001, 112724],
    [820001, 117657],
    [840001, 118623],
    [860001, 120782],
    [880001, 125627],
    [900001, 127480],
    [920001, 129644],
    [940001, 135568],
    [960001, 137741],
    [980001, 139996],
    [1000001, 141906],
    [1020001, 146854],
    [1040001, 148018],
    [1060001, 152693],
    [1080001, 155871],
    [1100001, 159407],
    [1120001, 161861],
    [1140001, 164424],
    [1160001, 168658],
    [1180001, 168939],
    [1200001, 173732],
    [1220001, 175124],
    [1240001, 178549],
    [1260001, 182816],
    [1280001, 184705],
    [1300001, 187817],
    [1320001, 192779],
    [1340001, 194278],
    [1360001, 198430],
    [1380001, 204078],
    [1400001, 205282],
    [1420001, 207496],
    [1440001, 210108],
    [1460001, 212893],
    [1480001, 217607],
    [1500001, 221116],
    [1520001, 222478],
    [1540001, 224950],
    [1560001, 230758],
    [1580001, 233966],
    [1600001, 235862],
    [1620001, 239481],
    [1640001, 243222],
    [1660001, 242148],
    [1680001, 248356],
    [1700001, 251191],
    [1720001, 253902],
    [1740001, 257271],
    [1760001, 262042],
    [1780001, 264376],
    [1800001, 268201],
    [1820001, 270984],
    [1840001, 271445],
    [1860001, 273889],
    [1880001, 282922],
    [1900001, 283890],
    [1920001, 287405],
    [1940001, 290087],
    [1960001, 295528],
    [1980001, 296719],
    [2000001, 302815],
    [2020001, 302361],
    [2040001, 300522],
    [2060001, 308385],
    [2080001, 310498],
    [2100001, 317080],
    [2120001, 318138],
    [2140001, 322269],
    [2160001, 322375],
    [2180001, 329263],
    [2200001, 329646],
    [2220001, 333488],
    [2240001, 339280],
    [2260001, 345075],
    [2280001, 343439],
    [2300001, 349191],
    [2320001, 348032],
    [2340001, 353348],
    [2360001, 362397],
    [2380001, 366604],
    [2400001, 364159],
    [2420001, 365635],
    [2440001, 372912],
    [2460001, 376433],
    [2480001, 379078],
    [2500001, 380030],
    [2520001, 378600],
    [2540001, 386691],
    [2560001, 388890],
    [2580001, 396441],
    [2600001, 398856],
    [2620001, 402402],
    [2640001, 401455],
    [2660001, 404390],
    [2680001, 411065],
    [2700001, 413969],
    [2720001, 411535],
    [2740001, 416351],
    [2760001, 421909],
    [2780001, 427666],
    [2800001, 428543],
    [2820001, 436558],
    [2840001, 435785],
    [2860001, 434126],
    [2880001, 442501],
    [2900001, 444719],
    [2920001, 447212],
    [2940001, 448014],
    [2960001, 452374],
    [2980001, 459045],
    [3000001, 458286],
    [3020001, 466145],
    [3040001, 465933],
    [3060001, 472866],
    [3080001, 472751],
    [3100001, 473248],
    [3120001, 477097],
    [3140001, 486647],
    [3160001, 487862],
    [3180001, 489746],
    [3200001, 493067],
    [3220001, 494486],
    [3240001, 504126],
    [3260001, 505870],
    [3280001, 507343],
    [3300001, 509690],
    [3320001, 516715],
    [3340001, 514543],
    [3360001, 517097],
    [3380001, 523909],
    [3400001, 529038],
    [3420001, 527240],
    [3440001, 532653],
    [3460001, 531407],
    [3480001, 544348],
    [3500001, 542198],
    [3520001, 551480],
    [3540001, 549721],
    [3560001, 552511],
    [3580001, 560945],
    [3600001, 561005],
    [3620001, 566159],
    [3640001, 566044],
    [3660001, 570061],
    [3680001, 570680],
    [3700001, 578540],
    [3720001, 581256],
    [3740001, 584993],
    [3760001, 582241],
    [3780001, 594264],
    [3800001, 594732],
    [3820001, 596355],
    [3840001, 598095],
    [3860001, 609738],
    [3880001, 606510],
    [3900001, 603718],
    [3920001, 623150],
    [3940001, 614644],
    [3960001, 617682],
    [3980001, 627926],
])
x, y = data.T
plt.scatter(x, y, marker="+", s=25, linewidths=1)
plt.show()
