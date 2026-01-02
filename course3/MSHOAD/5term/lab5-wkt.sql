use qgis;

-- 6.	Определите тип пространственных данных во всех таблицах
SELECT TABLE_NAME, COLUMN_NAME, DATA_TYPE
FROM INFORMATION_SCHEMA.COLUMNS
WHERE TABLE_SCHEMA = 'dbo'
-- 7.	Определите SRID - идентификатор системы координат
select distinct geom.STSrid as SRID from dbo.ne_10m_land
-- 8.	Определите атрибутивные столбцы
SELECT COLUMN_NAME, DATA_TYPE
FROM INFORMATION_SCHEMA.COLUMNS
WHERE TABLE_SCHEMA = 'dbo' AND DATA_TYPE != 'geometry'
-- 9.	Верните описания пространственных объектов в формате WKT
SELECT 
    [qgs_fid],
    [geom].STAsText() AS wkt,  
    [featurecla],
    [scalerank],
    [min_zoom]
FROM 
    [qgis].[dbo].[ne_10m_land]
WHERE 
    [geom] IS NOT NULL; 
-- 10.1.	Нахождение пересечения пространственных объектов;
SELECT obj1.geom.STIntersection(obj2.geom) AS Intersection
FROM ne_10m_land obj1, ne_10m_land obj2
WHERE obj1.qgs_fid = 1 AND obj2.qgs_fid = 2;
-- 10.2.	Нахождение объединения пространственных объектов;
SELECT obj1.geom.STUnion(obj2.geom) AS [Union]
FROM ne_10m_land obj1, ne_10m_land obj2
WHERE obj1.qgs_fid = 3 AND obj2.qgs_fid = 2;
-- 10.3.	Нахождение вложенности пространственных объектов;
SELECT obj1.geom.STWithin(obj2.geom) AS [IsWithin]
FROM ne_10m_land obj1, ne_10m_land obj2
WHERE obj1.qgs_fid = 1 AND obj2.qgs_fid = 2;
-- 10.4.	Упрощение пространственного объекта;
SELECT geom.Reduce(0.1) AS Simplified --насколько сильно должен быть упрощен геометрический объект
FROM ne_10m_land
WHERE qgs_fid = 6
-- 10.5.	Нахождение координат вершин пространственного объектов
SELECT geom.STPointN(1).ToString() AS VertexCoordinates
FROM ne_10m_land
WHERE qgs_fid = 6;
-- 10.6.	Нахождение размерности пространственных объектов
SELECT geom.STDimension() AS ObjectDimension
FROM ne_10m_land
WHERE qgs_fid = 3
-- 10.7.	Нахождение длины и площади пространственных объектов;
SELECT geom.STLength() AS ObjectLength, geom.STArea() AS ObjectArea
FROM ne_10m_land
WHERE qgs_fid = 5
-- 10.8.	Нахождение расстояния между пространственными объектами;
SELECT obj1.geom.STDistance(obj2.geom) AS Distance
FROM ne_10m_land obj1, ne_10m_land obj2
WHERE obj1.qgs_fid = 6 AND obj2.qgs_fid = 4
-- 11.	Создайте пространственный объект в виде точки (1) /линии (2) /полигона (3).
-- точка
DECLARE @pointGeometry GEOMETRY;
SET @pointGeometry = GEOMETRY::STGeomFromText('POINT(25 25)', 0);

SELECT @pointGeometry AS PointGeometry;

-- линия
DECLARE @lineGeometry GEOMETRY;
SET @lineGeometry = GEOMETRY::STGeomFromText('LINESTRING(20 5, 5 20, 25 25)', 0);

SELECT @lineGeometry AS LineGeometry;

-- полигон
DECLARE @polygonGeometry GEOMETRY;
SET @polygonGeometry = GEOMETRY::STGeomFromText('POLYGON((15 10, 55 55, 5 4, 12 2, 15 10))', 0);

SELECT @polygonGeometry AS PolygonGeometry;

-- 12.	Найдите, в какие пространственные объекты попадают созданные вами объекты

-- точка и полигон
DECLARE @point GEOMETRY = GEOMETRY::STGeomFromText('POINT(25 25)', 0);
DECLARE @polygon GEOMETRY = GEOMETRY::STGeomFromText('POLYGON((20 20, 20 40, 40 40, 40 20, 20 20))', 0);
SELECT @polygon AS PolygonGeometry;
SELECT @point.STWithin(@polygon) AS PointWithinPolygon;

-- прямая и полигон
DECLARE @line GEOMETRY = GEOMETRY::STGeomFromText('LINESTRING(20 5, 5 20, 25 25)', 0);
DECLARE @polygonn GEOMETRY = GEOMETRY::STGeomFromText('POLYGON((20 20, 20 40, 40 40, 40 20, 20 20))', 0);

SELECT @line.STIntersects(@polygonn) AS LineIntersectsPolygon;