CREATE VIEW [������ ��������������]
WITH SCHEMABINDING
AS
SELECT k.�������, k.���_�������, p.������
FROM dbo.[�����] k
JOIN dbo.[�������������] p ON k.���_������������� = p.���_�������������;