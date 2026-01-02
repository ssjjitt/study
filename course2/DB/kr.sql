use KP_base
--1.	Выбрать все заказы, выполненные после определенной даты.
select ORDER_NUM, ORDER_DATE from ORDERS where ORDER_DATE > '2008-02-12'
--2.	Выбрать все офисы из определенного региона и управляемые определенным сотрудником.
select OFFICE, REGION, NAME from OFFICES a
join SALESREPS aa on a.OFFICE = aa.REP_OFFICE
where a.REGION = 'Western' and aa.NAME = 'Larry Fitch'
--3.	Выбрать заказы, сделанные в определенный период.
select ORDER_NUM, ORDER_DATE from ORDERS where ORDER_DATE between '2008-01-15' and '2008-02-01'
--4.	Выбрать офисы из 12, 13 и 21 региона.
select OFFICE, REGION from OFFICES where OFFICE in (12, 13, 21)
--5.	Выбрать сотрудника, у которого нет менеджера (самого главного).
select EMPL_NUM, NAME from SALESREPS where MANAGER is null; 
--6.	Выбрать офисы из региона, который начинается на East.
select OFFICE, REGION from OFFICES where REGION like 'East%'
--7.	Выбрать фамилии и даты найма всех сотрудников и отсортировать по возрасту.
select NAME, HIRE_DATE, AGE from SALESREPS order by AGE
--8.	Выбрать все заказы и отсортировать вначале по стоимости по убыванию, а затем по количеству заказанного по возрастанию.
select ORDER_NUM, AMOUNT, QTY from ORDERS order by AMOUNT desc
select ORDER_NUM, AMOUNT, QTY from ORDERS order by QTY asc
--9.	Выбрать 5 самых дорогих товаров.
select top 5 DESCRIPTION, PRICE from PRODUCTS order by PRICE desc;
--10.	Выбрать 20% самых дорогих заказов.
select top 20 PERCENT ORDER_DATE, AMOUNT from ORDERS order by AMOUNT desc;
--11.	Выбрать сотрудников с 4 по 7, отсортированных по дате найма.
select NAME, HIRE_DATE from SALESREPS order by HIRE_DATE desc offset 4  rows fetch next 3 rows only;
--12.	Выбрать уникальные товары в заказах.
select distinct PRODUCT from ORDERS;
--13.	Подсчитать количество заказов для каждого покупателя.
select CUST_NUM, count(ORDER_NUM) as количество from CUSTOMERS a join ORDERS aa on a.CUST_NUM = aa.CUST group by CUST_NUM;
--14.	Подсчитать итоговую сумму заказа для каждого покупателя.
select CUST_NUM, sum(AMOUNT) as количество from CUSTOMERS a join ORDERS aa on a.CUST_NUM = aa.CUST group by CUST_NUM;
--15.	Подсчитать среднюю цену заказа для каждого сотрудника.
select EMPL_NUM, avg(AMOUNT) as ср_цена from SALESREPS a join ORDERS aa on a.EMPL_NUM = aa.REP group by EMPL_NUM;
--16.	Найти самый дорогой товар каждого производителя.
--17.	Найти покупателей и их заказы (в результирующем наборе должны быть: наименование покупателя, наименование товара, производитель, количество и итоговая сумма).
select COMPANY, PRODUCT, MFR, QTY, AMOUNT from CUSTOMERS a join ORDERS aa on a.CUST_NUM = aa.CUST;
--18.	Найти всех покупателей и их заказы.
select COMPANY, PRODUCT from CUSTOMERS a join ORDERS aa on a.CUST_NUM = aa.CUST;
--19.	Найти покупателей, у которых нет заказов.
select c.COMPANY from CUSTOMERS c left join ORDERS o on c.CUST_NUM = o.CUST where o.ORDER_NUM is null;
--20.	Найти покупателей, у которых есть заказы в определенный период.
select c.COMPANY from CUSTOMERS c join ORDERS o on c.CUST_NUM = o.CUST where o.ORDER_DATE between '2008-01-11' and '2008-01-31';
--21.	Найти товары, которые купили покупатели с кредитным лимитом больше 40000.
select COMPANY, PRODUCT, CREDIT_LIMIT from CUSTOMERS a join ORDERS aa on a.CUST_NUM = aa.CUST where CREDIT_LIMIT > 40000;
--22.	Найти сотрудников одного возраста.
select NAME, HIRE_DATE, AGE from SALESREPS where AGE = 33;
--23.	Выбрать всех покупателей в порядке уменьшения обшей стоимости заказов.
select CUST_NUM, sum(AMOUNT) as [Total] from CUSTOMERS a join ORDERS aa on a.CUST_NUM = aa.CUST group by CUST_NUM order by [Total] desc;
--24.	Выбрать заказы, сумма которых больше среднего значения.
select PRODUCT, sum(AMOUNT), avg(AMOUNT) from ORDERS group by PRODUCT having sum(AMOUNT) > avg(AMOUNT);
--25.	Подсчитать, на какую сумму каждый офис выполнил заказы, и отсортировать их в порядке убывания.
select OFFICE, SALES from OFFICES order by SALES desc;

--26.	Выбрать сотрудников, которые являются начальниками (у которых есть подчиненные).
select NAME, MANAGER from SALESREPS where EMPL_NUM in (select distinct MANAGER from SALESREPS where MANAGER is not null);
--27.	Выбрать сотрудников, которые не являются начальниками (у которых нет подчиненных).
select NAME, MANAGER from SALESREPS where EMPL_NUM not in (select distinct MANAGER from SALESREPS);

--28.	Выбрать всех продукты, продаваемые менеджерами из восточного региона.
select 


use KP_base
--1.	Выбрать все заказы, выполненные после определенной даты.
select ORDER_NUM, ORDER_DATE from ORDERS where ORDER_DATE > '2008-02-12'
--2.	Выбрать все офисы из определенного региона и управляемые определенным сотрудником.
select OFFICE, REGION, NAME from OFFICES a
join SALESREPS aa on a.OFFICE = aa.REP_OFFICE
where a.REGION = 'Western' and aa.NAME = 'Larry Fitch'
--3.	Выбрать заказы, сделанные в определенный период.
select ORDER_NUM, ORDER_DATE from ORDERS where ORDER_DATE between '2008-01-15' and '2008-02-01'
--4.	Выбрать офисы из 12, 13 и 21 региона.
select OFFICE, REGION from OFFICES where OFFICE in (12, 13, 21)
--5.	Выбрать сотрудника, у которого нет менеджера (самого главного).
select EMPL_NUM, NAME from SALESREPS where MANAGER is null; 
--6.	Выбрать офисы из региона, который начинается на East.
select OFFICE, REGION from OFFICES where REGION like 'East%'
--7.	Выбрать фамилии и даты найма всех сотрудников и отсортировать по возрасту.
select NAME, HIRE_DATE, AGE from SALESREPS order by AGE
--8.	Выбрать все заказы и отсортировать вначале по стоимости по убыванию, а затем по количеству заказанного по возрастанию.
select ORDER_NUM, AMOUNT, QTY from ORDERS order by AMOUNT desc
select ORDER_NUM, AMOUNT, QTY from ORDERS order by QTY asc
--9.	Выбрать 5 самых дорогих товаров.
select top 5 DESCRIPTION, PRICE from PRODUCTS order by PRICE desc;
--10.	Выбрать 20% самых дорогих заказов.
select top 20 PERCENT ORDER_DATE, AMOUNT from ORDERS order by AMOUNT desc;
--11.	Выбрать сотрудников с 4 по 7, отсортированных по дате найма.
select NAME, HIRE_DATE from SALESREPS order by HIRE_DATE desc offset 4  rows fetch next 3 rows only;
--12.	Выбрать уникальные товары в заказах.
select distinct PRODUCT from ORDERS;
--13.	Подсчитать количество заказов для каждого покупателя.
select CUST_NUM, count(ORDER_NUM) as количество from CUSTOMERS a join ORDERS aa on a.CUST_NUM = aa.CUST group by CUST_NUM;
--14.	Подсчитать итоговую сумму заказа для каждого покупателя.
select CUST_NUM, sum(AMOUNT) as количество from CUSTOMERS a join ORDERS aa on a.CUST_NUM = aa.CUST group by CUST_NUM;
--15.	Подсчитать среднюю цену заказа для каждого сотрудника.
select EMPL_NUM, avg(AMOUNT) as ср_цена from SALESREPS a join ORDERS aa on a.EMPL_NUM = aa.REP group by EMPL_NUM;
--16.	Найти самый дорогой товар каждого производителя.
select MFR_ID, max(PRICE) as [цена^] from PRODUCTS group by MFR_ID;
--17.	Найти покупателей и их заказы (в результирующем наборе должны быть: наименование покупателя, наименование товара, производитель, количество и итоговая сумма).
select COMPANY, PRODUCT, MFR, QTY, AMOUNT from CUSTOMERS a join ORDERS aa on a.CUST_NUM = aa.CUST;
--18.	Найти всех покупателей и их заказы.
select COMPANY, PRODUCT from CUSTOMERS a join ORDERS aa on a.CUST_NUM = aa.CUST;
--19.	Найти покупателей, у которых нет заказов.
select c.COMPANY from CUSTOMERS c left join ORDERS o on c.CUST_NUM = o.CUST where o.ORDER_NUM is null;
--20.	Найти покупателей, у которых есть заказы в определенный период.
select c.COMPANY from CUSTOMERS c join ORDERS o on c.CUST_NUM = o.CUST where o.ORDER_DATE between '2008-01-11' and '2008-01-31';
--21.	Найти товары, которые купили покупатели с кредитным лимитом больше 40000.
select COMPANY, PRODUCT, CREDIT_LIMIT from CUSTOMERS a join ORDERS aa on a.CUST_NUM = aa.CUST where CREDIT_LIMIT > 40000;
--22.	Найти сотрудников одного возраста.
select NAME, HIRE_DATE, AGE from SALESREPS where AGE = 33;
--23.	Выбрать всех покупателей в порядке уменьшения обшей стоимости заказов.
select CUST_NUM, sum(AMOUNT) as [Total] from CUSTOMERS a join ORDERS aa on a.CUST_NUM = aa.CUST group by CUST_NUM order by [Total] desc;
--24.	Выбрать заказы, сумма которых больше среднего значения.
select PRODUCT, sum(AMOUNT), avg(AMOUNT) from ORDERS group by PRODUCT having sum(AMOUNT) > avg(AMOUNT);
--25.	Подсчитать, на какую сумму каждый офис выполнил заказы, и отсортировать их в порядке убывания.
SELECT OFFICE, SUM(AMOUNT) AS TOTAL_AMOUNT FROM ORDERS JOIN OFFICES ON ORDERS.REP = OFFICES.MGR GROUP BY OFFICE ORDER BY TOTAL_AMOUNT DESC;
--26.	Выбрать сотрудников, которые являются начальниками (у которых есть подчиненные).
SELECT * FROM SALESREPS WHERE EMPL_NUM IN (SELECT DISTINCT MANAGER FROM SALESREPS WHERE MANAGER IS NOT NULL);
--27.	Выбрать сотрудников, которые не являются начальниками (у которых нет подчиненных).
SELECT *
FROM SALESREPS
WHERE EMPL_NUM NOT IN (SELECT DISTINCT MANAGER FROM SALESREPS WHERE MANAGER IS NOT NULL);
--28.	Выбрать всех продукты, продаваемые менеджерами из восточного региона.
SELECT PRODUCTS.*, REGION
FROM PRODUCTS
JOIN ORDERS ON PRODUCTS.MFR_ID = ORDERS.MFR AND PRODUCTS.PRODUCT_ID = ORDERS.PRODUCT
JOIN SALESREPS ON ORDERS.REP = SALESREPS.EMPL_NUM
JOIN OFFICES ON OFFICES.OFFICE = SALESREPS.REP_OFFICE
WHERE OFFICES.REGION = 'Eastern';
--29.	Выбрать товары, которые по стоимости ниже среднего значения стоимости заказа по покупателю.
SELECT PRODUCTS.*
FROM PRODUCTS
WHERE PRODUCTS.PRICE < (
  SELECT AVG(ORDERS.AMOUNT)
  FROM ORDERS
)
--30. Найти организации, которые не делали заказы в 2008, но делали в 2007 (как минимум 2-мя разными способами).
SELECT CUSTOMERS.COMPANY
FROM CUSTOMERS
WHERE CUSTOMERS.CUST_NUM NOT IN (
  SELECT DISTINCT ORDERS.CUST
  FROM ORDERS
  WHERE YEAR(ORDERS.ORDER_DATE) = 2006
)
AND CUSTOMERS.CUST_NUM IN (
  SELECT DISTINCT ORDERS.CUST
  FROM ORDERS
  WHERE YEAR(ORDERS.ORDER_DATE) = 2007
  GROUP BY ORDERS.CUST
  HAVING COUNT(DISTINCT ORDERS.ORDER_NUM) >= 2
);
SELECT CUSTOMERS.COMPANY
FROM CUSTOMERS
WHERE NOT EXISTS (
  SELECT 1
  FROM ORDERS
  WHERE ORDERS.CUST = CUSTOMERS.CUST_NUM AND YEAR(ORDERS.ORDER_DATE) = 2006
)
AND EXISTS (
  SELECT 1
  FROM ORDERS
  WHERE ORDERS.CUST = CUSTOMERS.CUST_NUM AND YEAR(ORDERS.ORDER_DATE) = 2007
  GROUP BY ORDERS.CUST
  HAVING COUNT(DISTINCT ORDERS.ORDER_NUM) >= 2
);







