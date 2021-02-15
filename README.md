## Быстрая билатеральная фильраця

[оригинальная статья](http://vestnik.rsreu.ru/images/archive/2018/4-66-1/2.4_.pdf)
 авторы А. И. Новиков, А. В. Пронькин;

авторы используют простую аддитивная модель: 
![](http://latex.codecogs.com/gif.latex?%5Cdpi%7B100%7D%20I__%7Bij%7D%20=%20U___%7Bij%7D%20%20&plus;%20%7B%5Cxi%7D_%7Bij%7D)

где:
![](http://latex.codecogs.com/gif.latex?\dpi{100}&space;I__{ij}) - исходное изображение
![](http://latex.codecogs.com/gif.latex?\dpi{100}&space;U_{ij}) - полезный сигнал
![](http://latex.codecogs.com/gif.latex?\dpi{100}&space;{\xi}_{ij}) -  помехи

###проблематика в рассмотренная в статье:
Наибольшие искажения при работе обыных фильров, основанных на линейных операторах, например [медианного](https://github.com/alehay/median_filter) происходят на границе резкого перепада яркостей:
![](https://github.com/alehay/bilateral_filter/blob/main/staff/linear.png)

###предложенное решение:
Авторы статьи предлагают использовать билатеральный фильтр , основанный на нелинейном операторе:

![](https://latex.codecogs.com/gif.latex?%5Chuge%20%5Cfrac%7B%7B%5Csum_%7Bs%3D-k%7D%5Ek%7D%7B%5Csum_%7Bt%3D-k%7D%5Ek%7DI_%7Bi&plus;s%2Cj&plus;t%7D*W_%7Bst%7D%7D%7B%7B%20%5Csum_%7Bs%3D-k%7D%5Ek%7D%7B%5Csum_%7Bt%3D-k%7D%5Ek%7D*%7BW_%7Bst%7D%7D%7D%29)  



где 
![](http://latex.codecogs.com/gif.latex?\dpi{120}&space;W_{st}&space;=&space;e^{-\frac{s^2&space;&plus;&space;t^2}&space;{2k^2}}&space;*&space;&space;e^{-\frac{I__{i&plus;s,j&plus;t}&space;-&space;I__{ij}}&space;{2d^2}}&space;)

в свою очередь:
![](http://latex.codecogs.com/gif.latex?\dpi{100}&space;e^{-\frac{s^2&space;&plus;&space;t^2}&space;{2k^2}})-множитель расстояния :
![](http://latex.codecogs.com/gif.latex?\dpi{100}&space;e^{-\frac{I__{i&plus;s,j&plus;t}&space;-&space;I__{ij}}&space;{2d^2}}&space;) -множитель разности в яркости ;

смысл данного данного филтра прост: 

по изображению движется область "ядро", в центре которого расположен целевой пиксель, к которому применяется результат работы фильтра на текущей итерации. 
Все пиксели из ядря складываются по яркости, но вклад каждого, определяется его "весом". 
Вес пикселя зависит от разности в яркости и его удаленности от целевого пикселя. 



https://github.com/alehay/median_filter

$$\sin(\alpha)^{\theta}=\sum_{i=0}^{n}(x^i + \cos(f))$$
