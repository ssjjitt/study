use lab10;

exec sp_configure 'show advanced options', 1;
exec sp_configure 'clr enabled',1;
exec sp_configure 'clr strict security', 0

USE master;
GO
CREATE ASYMMETRIC KEY PhoneNumberKey FROM EXECUTABLE FILE = 'D:\univer\!МСХОАД\lab10\lab10\bin\Debug\lab10.dll';
GO
CREATE LOGIN PhoneNumberKeyLogin FROM ASYMMETRIC KEY PhoneNumberKey;
GO
GRANT UNSAFE ASSEMBLY TO PhoneNumberKeyLogin;
GO
CREATE USER PhoneNumberKeyLogin FOR LOGIN PhoneNumberKeyLogin;
GO
CREATE ASSEMBLY PhoneNumberAssembly FROM 'D:\univer\!МСХОАД\lab10\lab10\bin\Debug\lab10.dll' WITH PERMISSION_SET = UNSAFE;
GO

-----lab10!!!!!!!!

SELECT * FROM sys.assemblies WHERE name = 'PhoneNumberAssembly';
SELECT * FROM sys.types WHERE name = 'PhoneNumber';
-----

CREATE TYPE PhoneNumber EXTERNAL NAME PhoneNumberAssembly.[PhoneNumLogger.PhoneNumber];

CREATE PROCEDURE LogPhoneNumber
@phoneNumber PhoneNumber
AS EXTERNAL NAME PhoneNumberAssembly.[PhoneNumLogger.PhoneNumberLogger].LogPhoneNumber;
go

DECLARE @phone PhoneNumber;
SET @phone = '1234567890';
EXEC LogPhoneNumber @phone;

--DROP ASSEMBLY PhoneNumberAssembly
--drop TYPE PhoneNumber
--drop PROCEDURE LogPhoneNumber