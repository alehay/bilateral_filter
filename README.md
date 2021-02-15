## Быстрая билатеральная фильраця

[оригинальная статья](http://vestnik.rsreu.ru/images/archive/2018/4-66-1/2.4_.pdf)
 авторы А. И. Новиков, А. В. Пронькин;

авторы используют простую аддитивная модель: 
![](https://latex.codecogs.com/gif.latex?\LARGE&space;I__{ij}&space;=&space;U___{ij}&space;&plus;&space;{\xi}_{ij})

где:
$$I__{ij} $$ - исходное изображение
$$U_{ij} $$ - полезный сигнал
$${\xi}_{ij} $$  помехи

####проблематика в рассмотренная в статье:
Наибольшие искажения при работе обыных фильров, основанных на линейных операторах, например [медианного](https://github.com/alehay/median_filter) происходят на границе резкого перепада яркостей.

TODO вставить пример, размытия

####предложенное решение:
Авторы статьи предлагают использовать билатеральный фильтр , основанный на нелинейном операторе:

![equation](https://render.githubusercontent.com/render/math?math=\frac{{\sum_{s=-k}^k}{\sum_{t=-k}^k}I_{i+s,j+t}*W_{st}}{{ \sum_{s=-k}^k}{\sum_{t=-k}^k}{W_{st}}})


![](https://latex.codecogs.com/gif.latex?%5Chuge%20%5Cfrac%7B%7B%5Csum_%7Bs%3D-k%7D%5Ek%7D%7B%5Csum_%7Bt%3D-k%7D%5Ek%7DI_%7Bi&plus;s%2Cj&plus;t%7D*W_%7Bst%7D%7D%7B%7B%20%5Csum_%7Bs%3D-k%7D%5Ek%7D%7B%5Csum_%7Bt%3D-k%7D%5Ek%7D*%7BW_%7Bst%7D%7D%7D%29)  

"$e^{i \\pi} = -1$"


где 
$$  W_{st} = e^{-\frac{s^2 + t^2} {2k^2}} *  e^{-\frac{I__{i+s,j+t} - I__{ij}} {2d^2}} 
$$

множитель расстояния :
$$ e^{-\frac{s^2 + t^2} {2k^2}}$$

множитель разности в яркости:
$$ 
e^{-\frac{I__{i+s,j+t} - I__{ij}} {2d^2}} 
$$

смысл данного данного филтра прост: 

по изображению движется область "ядро", в центре которого расположен целевой пиксель, к которому применяется результат работы фильтра на текущей итерации. 
Все пиксели из ядря складываются по яркости, но вклад каждого, определяется его "весом". 
Вес пикселя зависит от разности в яркости и его удаленности от целевого пикселя. 



https://github.com/alehay/median_filter

$$\sin(\alpha)^{\theta}=\sum_{i=0}^{n}(x^i + \cos(f))$$
