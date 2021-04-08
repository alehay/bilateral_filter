# Быстрая билатеральная фильтрация

[оригинальная статья](http://vestnik.rsreu.ru/images/archive/2018/4-66-1/2.4_.pdf)
 авторы А. И. Новиков, А. В. Пронькин;

авторы используют простую аддитивную модель: 
<img src="https://render.githubusercontent.com/render/math?math=\LARGE I_{ij}=U_{ij}%2B\xi_{ij}">

где:
<img src="https://render.githubusercontent.com/render/math?math=\LARGE I_{ij}"> - исходное изображение;

<img src="https://render.githubusercontent.com/render/math?math=\LARGE U_{ij}"> - полезный сигнал;

<img src="https://render.githubusercontent.com/render/math?math=\LARGE \xi_{ij}"> -  помехи;


### Проблематика, рассмотренная в статье:

Наибольшие искажения при работе обычных фильтров, основанных на линейных операторах, например [медианного](https://github.com/alehay/median_filter) происходят на границе резкого перепада яркостей:

![](https://github.com/alehay/bilateral_filter/blob/main/staff/linear.png)

### Предложенное решение:
Авторы статьи предлагают использовать билатеральный фильтр , основанный на нелинейном операторе:

<img src="https://render.githubusercontent.com/render/math?math=\LARGE \frac{\sum_{s=-k}^{k}\sum_{t=-k}^{k} I_{i%2Bs,j%2Bt} \cdot W_{st}}{\sum_{s=-k}^{k}\sum_{t=-k}^{k} I_{i%2Bs,j%2Bt} W_{st}}">


где:  

<img src="https://render.githubusercontent.com/render/math?math=\LARGE W_{st}=e^{-\frac{s^2%2Bt^2}{2k^2}} \cdot e^{-\frac{I_{i%2Bs,j%2Bt}-I_{ij}}{2d^2}}">


в свою очередь:

<img src="https://render.githubusercontent.com/render/math?math=\LARGE e^{-\frac{s^2%2Bt^2}{2k^2}}"> &ndash; множитель расстояния;

<img src="https://render.githubusercontent.com/render/math?math=\LARGE e^{-\frac{I_{i%2Bs,j%2Bt}-I_{ij}}{2d^2}}"> &ndash; множитель разности в яркости;

### Сравнение: 
1) Без фильтра:

![](https://github.com/alehay/median_filter/blob/main/build-Debug/out/non_filter.png)

2) Медианный:

![](https://github.com/alehay/median_filter/blob/main/build-Debug/out/13.png)

3) Билатеральный:

![](https://github.com/alehay/bilateral_filter/blob/main/staff/1__k10__d25.png)



### Смысл данного данного фильтра прост: 

по изображению движется область "ядро", в центре которого расположен целевой пиксель, к которому применяется результат работы фильтра на текущей итерации. 
Все пиксели из ядря складываются по яркости, но вклад каждого, определяется его "весом". 
Вес пикселя зависит от разности в яркости и его удаленности от целевого пикселя. 


![](https://github.com/alehay/bilateral_filter/blob/main/staff/befor.png)
![](https://github.com/alehay/bilateral_filter/blob/main/staff/after.png)


### Быстродействие:
Существенным недостатком билатерального фильтра  является  низкое  быстродействие,  обусловленное  высокими  вычислительными  затратами.  На  обработку  рассматриваемого  изображения. Повысить быстродейтсвие вычислив заранее для заданных значений параметров значения весовых коэффициентов.

gif  ядро с плечем 8 параметр d от 5 до 45 с шагом 5

![](https://github.com/alehay/bilateral_filter/blob/main/staff/k_8.gif)

ядро с плечем 17 параметр d от 5 до 45 c шагом 5

![](https://github.com/alehay/bilateral_filter/blob/main/staff/k_17.gif)

ядро с плечем 23 d от 5 до 45 с шагом 5 

![](https://github.com/alehay/bilateral_filter/blob/main/staff/k_23.gif)
