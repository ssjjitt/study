USE master
GO
CREATE DATABASE Gl_MyBase2
on primary
(name = N'MyBase_mdf', filename = N'E:\����\��\MyBase_mdf.mdf', size = 10240Kb, maxsize = UNLIMITED, filegrowth = 1024Kb)
log on 
(name = N'MyBase_log', filename = N'E:\����\��\MyBase_log.log', size = 10240Kb, maxsize = 2048Gb, filegrowth = 10%)
GO