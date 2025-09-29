use KP_base
--1.	������� ��� ������, ����������� ����� ������������ ����.
select ORDER_NUM, ORDER_DATE from ORDERS where ORDER_DATE > '2008-02-12'
--2.	������� ��� ����� �� ������������� ������� � ����������� ������������ �����������.
select OFFICE, REGION, NAME from OFFICES a
join SALESREPS aa on a.OFFICE = aa.REP_OFFICE
where a.REGION = 'Western' and aa.NAME = 'Larry Fitch'
--3.	������� ������, ��������� � ������������ ������.
select ORDER_NUM, ORDER_DATE from ORDERS where ORDER_DATE between '2008-01-15' and '2008-02-01'
--4.	������� ����� �� 12, 13 � 21 �������.
select OFFICE, REGION from OFFICES where OFFICE in (12, 13, 21)
--5.	������� ����������, � �������� ��� ��������� (������ ��������).
select EMPL_NUM, NAME from SALESREPS where MANAGER is null; 
--6.	������� ����� �� �������, ������� ���������� �� East.
select OFFICE, REGION from OFFICES where REGION like 'East%'
--7.	������� ������� � ���� ����� ���� ����������� � ������������� �� ��������.
select NAME, HIRE_DATE, AGE from SALESREPS order by AGE
--8.	������� ��� ������ � ������������� ������� �� ��������� �� ��������, � ����� �� ���������� ����������� �� �����������.
select ORDER_NUM, AMOUNT, QTY from ORDERS order by AMOUNT desc
select ORDER_NUM, AMOUNT, QTY from ORDERS order by QTY asc
--9.	������� 5 ����� ������� �������.
select top 5 DESCRIPTION, PRICE from PRODUCTS order by PRICE desc;
--10.	������� 20% ����� ������� �������.
select top 20 PERCENT ORDER_DATE, AMOUNT from ORDERS order by AMOUNT desc;
--11.	������� ����������� � 4 �� 7, ��������������� �� ���� �����.
select NAME, HIRE_DATE from SALESREPS order by HIRE_DATE desc offset 4  rows fetch next 3 rows only;
--12.	������� ���������� ������ � �������.
select distinct PRODUCT from ORDERS;
--13.	���������� ���������� ������� ��� ������� ����������.
select CUST_NUM, count(ORDER_NUM) as ���������� from CUSTOMERS a join ORDERS aa on a.CUST_NUM = aa.CUST group by CUST_NUM;
--14.	���������� �������� ����� ������ ��� ������� ����������.
select CUST_NUM, sum(AMOUNT) as ���������� from CUSTOMERS a join ORDERS aa on a.CUST_NUM = aa.CUST group by CUST_NUM;
--15.	���������� ������� ���� ������ ��� ������� ����������.
select EMPL_NUM, avg(AMOUNT) as ��_���� from SALESREPS a join ORDERS aa on a.EMPL_NUM = aa.REP group by EMPL_NUM;
--16.	����� ����� ������� ����� ������� �������������.
--17.	����� ����������� � �� ������ (� �������������� ������ ������ ����: ������������ ����������, ������������ ������, �������������, ���������� � �������� �����).
select COMPANY, PRODUCT, MFR, QTY, AMOUNT from CUSTOMERS a join ORDERS aa on a.CUST_NUM = aa.CUST;
--18.	����� ���� ����������� � �� ������.
select COMPANY, PRODUCT from CUSTOMERS a join ORDERS aa on a.CUST_NUM = aa.CUST;
--19.	����� �����������, � ������� ��� �������.
select c.COMPANY from CUSTOMERS c left join ORDERS o on c.CUST_NUM = o.CUST where o.ORDER_NUM is null;
--20.	����� �����������, � ������� ���� ������ � ������������ ������.
select c.COMPANY from CUSTOMERS c join ORDERS o on c.CUST_NUM = o.CUST where o.ORDER_DATE between '2008-01-11' and '2008-01-31';
--21.	����� ������, ������� ������ ���������� � ��������� ������� ������ 40000.
select COMPANY, PRODUCT, CREDIT_LIMIT from CUSTOMERS a join ORDERS aa on a.CUST_NUM = aa.CUST where CREDIT_LIMIT > 40000;
--22.	����� ����������� ������ ��������.
select NAME, HIRE_DATE, AGE from SALESREPS where AGE = 33;
--23.	������� ���� ����������� � ������� ���������� ����� ��������� �������.
select CUST_NUM, sum(AMOUNT) as [Total] from CUSTOMERS a join ORDERS aa on a.CUST_NUM = aa.CUST group by CUST_NUM order by [Total] desc;
--24.	������� ������, ����� ������� ������ �������� ��������.
select PRODUCT, sum(AMOUNT), avg(AMOUNT) from ORDERS group by PRODUCT having sum(AMOUNT) > avg(AMOUNT);
--25.	����������, �� ����� ����� ������ ���� �������� ������, � ������������� �� � ������� ��������.
select OFFICE, SALES from OFFICES order by SALES desc;

--26.	������� �����������, ������� �������� ������������ (� ������� ���� �����������).
select NAME, MANAGER from SALESREPS where EMPL_NUM in (select distinct MANAGER from SALESREPS where MANAGER is not null);
--27.	������� �����������, ������� �� �������� ������������ (� ������� ��� �����������).
select NAME, MANAGER from SALESREPS where EMPL_NUM not in (select distinct MANAGER from SALESREPS);

--28.	������� ���� ��������, ����������� ����������� �� ���������� �������.
select 


use KP_base
--1.	������� ��� ������, ����������� ����� ������������ ����.
select ORDER_NUM, ORDER_DATE from ORDERS where ORDER_DATE > '2008-02-12'
--2.	������� ��� ����� �� ������������� ������� � ����������� ������������ �����������.
select OFFICE, REGION, NAME from OFFICES a
join SALESREPS aa on a.OFFICE = aa.REP_OFFICE
where a.REGION = 'Western' and aa.NAME = 'Larry Fitch'
--3.	������� ������, ��������� � ������������ ������.
select ORDER_NUM, ORDER_DATE from ORDERS where ORDER_DATE between '2008-01-15' and '2008-02-01'
--4.	������� ����� �� 12, 13 � 21 �������.
select OFFICE, REGION from OFFICES where OFFICE in (12, 13, 21)
--5.	������� ����������, � �������� ��� ��������� (������ ��������).
select EMPL_NUM, NAME from SALESREPS where MANAGER is null; 
--6.	������� ����� �� �������, ������� ���������� �� East.
select OFFICE, REGION from OFFICES where REGION like 'East%'
--7.	������� ������� � ���� ����� ���� ����������� � ������������� �� ��������.
select NAME, HIRE_DATE, AGE from SALESREPS order by AGE
--8.	������� ��� ������ � ������������� ������� �� ��������� �� ��������, � ����� �� ���������� ����������� �� �����������.
select ORDER_NUM, AMOUNT, QTY from ORDERS order by AMOUNT desc
select ORDER_NUM, AMOUNT, QTY from ORDERS order by QTY asc
--9.	������� 5 ����� ������� �������.
select top 5 DESCRIPTION, PRICE from PRODUCTS order by PRICE desc;
--10.	������� 20% ����� ������� �������.
select top 20 PERCENT ORDER_DATE, AMOUNT from ORDERS order by AMOUNT desc;
--11.	������� ����������� � 4 �� 7, ��������������� �� ���� �����.
select NAME, HIRE_DATE from SALESREPS order by HIRE_DATE desc offset 4  rows fetch next 3 rows only;
--12.	������� ���������� ������ � �������.
select distinct PRODUCT from ORDERS;
--13.	���������� ���������� ������� ��� ������� ����������.
select CUST_NUM, count(ORDER_NUM) as ���������� from CUSTOMERS a join ORDERS aa on a.CUST_NUM = aa.CUST group by CUST_NUM;
--14.	���������� �������� ����� ������ ��� ������� ����������.
select CUST_NUM, sum(AMOUNT) as ���������� from CUSTOMERS a join ORDERS aa on a.CUST_NUM = aa.CUST group by CUST_NUM;
--15.	���������� ������� ���� ������ ��� ������� ����������.
select EMPL_NUM, avg(AMOUNT) as ��_���� from SALESREPS a join ORDERS aa on a.EMPL_NUM = aa.REP group by EMPL_NUM;
--16.	����� ����� ������� ����� ������� �������������.
select MFR_ID, max(PRICE) as [����^] from PRODUCTS group by MFR_ID;
--17.	����� ����������� � �� ������ (� �������������� ������ ������ ����: ������������ ����������, ������������ ������, �������������, ���������� � �������� �����).
select COMPANY, PRODUCT, MFR, QTY, AMOUNT from CUSTOMERS a join ORDERS aa on a.CUST_NUM = aa.CUST;
--18.	����� ���� ����������� � �� ������.
select COMPANY, PRODUCT from CUSTOMERS a join ORDERS aa on a.CUST_NUM = aa.CUST;
--19.	����� �����������, � ������� ��� �������.
select c.COMPANY from CUSTOMERS c left join ORDERS o on c.CUST_NUM = o.CUST where o.ORDER_NUM is null;
--20.	����� �����������, � ������� ���� ������ � ������������ ������.
select c.COMPANY from CUSTOMERS c join ORDERS o on c.CUST_NUM = o.CUST where o.ORDER_DATE between '2008-01-11' and '2008-01-31';
--21.	����� ������, ������� ������ ���������� � ��������� ������� ������ 40000.
select COMPANY, PRODUCT, CREDIT_LIMIT from CUSTOMERS a join ORDERS aa on a.CUST_NUM = aa.CUST where CREDIT_LIMIT > 40000;
--22.	����� ����������� ������ ��������.
select NAME, HIRE_DATE, AGE from SALESREPS where AGE = 33;
--23.	������� ���� ����������� � ������� ���������� ����� ��������� �������.
select CUST_NUM, sum(AMOUNT) as [Total] from CUSTOMERS a join ORDERS aa on a.CUST_NUM = aa.CUST group by CUST_NUM order by [Total] desc;
--24.	������� ������, ����� ������� ������ �������� ��������.
select PRODUCT, sum(AMOUNT), avg(AMOUNT) from ORDERS group by PRODUCT having sum(AMOUNT) > avg(AMOUNT);
--25.	����������, �� ����� ����� ������ ���� �������� ������, � ������������� �� � ������� ��������.
SELECT OFFICE, SUM(AMOUNT) AS TOTAL_AMOUNT FROM ORDERS JOIN OFFICES ON ORDERS.REP = OFFICES.MGR GROUP BY OFFICE ORDER BY TOTAL_AMOUNT DESC;
--26.	������� �����������, ������� �������� ������������ (� ������� ���� �����������).
SELECT * FROM SALESREPS WHERE EMPL_NUM IN (SELECT DISTINCT MANAGER FROM SALESREPS WHERE MANAGER IS NOT NULL);
--27.	������� �����������, ������� �� �������� ������������ (� ������� ��� �����������).
SELECT *
FROM SALESREPS
WHERE EMPL_NUM NOT IN (SELECT DISTINCT MANAGER FROM SALESREPS WHERE MANAGER IS NOT NULL);
--28.	������� ���� ��������, ����������� ����������� �� ���������� �������.
SELECT PRODUCTS.*, REGION
FROM PRODUCTS
JOIN ORDERS ON PRODUCTS.MFR_ID = ORDERS.MFR AND PRODUCTS.PRODUCT_ID = ORDERS.PRODUCT
JOIN SALESREPS ON ORDERS.REP = SALESREPS.EMPL_NUM
JOIN OFFICES ON OFFICES.OFFICE = SALESREPS.REP_OFFICE
WHERE OFFICES.REGION = 'Eastern';
--29.	������� ������, ������� �� ��������� ���� �������� �������� ��������� ������ �� ����������.
SELECT PRODUCTS.*
FROM PRODUCTS
WHERE PRODUCTS.PRICE < (
  SELECT AVG(ORDERS.AMOUNT)
  FROM ORDERS
)
--30. ����� �����������, ������� �� ������ ������ � 2008, �� ������ � 2007 (��� ������� 2-�� ������� ���������).
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







