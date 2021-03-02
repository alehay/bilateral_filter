# Быстрая билатеральная фильтрация

[оригинальная статья](http://vestnik.rsreu.ru/images/archive/2018/4-66-1/2.4_.pdf)
 авторы А. И. Новиков, А. В. Пронькин;

авторы используют простую аддитивную модель: 
![](http://latex.codecogs.com/gif.latex?\dpi{120}&space;$$I_{ij}&space;=&space;U_{ij}&space;&space;&plus;&space;{\xi}_{ij}&space;)

где:
![](http://latex.codecogs.com/gif.latex?\dpi{100}&space;I_{ij}) - исходное изображение;

![](http://latex.codecogs.com/gif.latex?\dpi{100}&space;U_{ij}) - полезный сигнал;

![](http://latex.codecogs.com/gif.latex?\dpi{100}&space;{\xi}_{ij}) -  помехи;


### Проблематика рассмотренная в статье:

Наибольшие искажения при работе обычных фильтров, основанных на линейных операторах, например [медианного](https://github.com/alehay/median_filter) происходят на границе резкого перепада яркостей:

![](https://github.com/alehay/bilateral_filter/blob/main/staff/linear.png)

### Предложенное решение:
Авторы статьи предлагают использовать билатеральный фильтр , основанный на нелинейном операторе:

![](http://latex.codecogs.com/gif.latex?\dpi{190}&space;\frac{{\sum_{s=-k}^k}{\sum_{t=-k}^k}I_{i&plus;s,j&plus;t}*W_{st}}{{&space;\sum_{s=-k}^k}{\sum_{t=-k}^k}*{W_{st}}}&space;)  


где:  

![](http://latex.codecogs.com/gif.latex?\dpi{200}&space;W_{st}&space;=&space;e^{-\frac{s^2&space;&plus;&space;t^2}&space;{2k^2}}&space;*&space;&space;e^{-\frac{I__{i&plus;s,j&plus;t}&space;-&space;I__{ij}}&space;{2d^2}}&space;)

в свою очередь:

![](http://latex.codecogs.com/gif.latex?\dpi{170}&space;e^{-\frac{s^2&space;&plus;&space;t^2}&space;{2k^2}})   -множитель расстояния;

![](http://latex.codecogs.com/gif.latex?\dpi{170}&space;e^{-\frac{I__{i&plus;s,j&plus;t}&space;-&space;I__{ij}}^2 &space;{2d^2}}&space;)   -множитель разности в яркости ;


### Смысл данного данного фильтра прост: 

по изображению движется область "ядро", в центре которого расположен целевой пиксель, к которому применяется результат работы фильтра на текущей итерации. 
Все пиксели из ядря складываются по яркости, но вклад каждого, определяется его "весом". 
Вес пикселя зависит от разности в яркости и его удаленности от целевого пикселя. 

### Быстродействие:
Существенным недостатком билатерального фильтра  является  низкое  быстродействие,  обусловленное  высокими  вычислительными  затратами.  На  обработку  рассматриваемого  изображения. Повысить быстродейтсвие вычислив заранее для заданных значений параметров значения весовых коэффициентов.
