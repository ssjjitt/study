CREATE VIEW [оплата преподавателей]
WITH SCHEMABINDING
AS
SELECT k.предмет, k.тип_зан€ти€, p.оплата
FROM dbo.[ урсы] k
JOIN dbo.[ѕреподаватели] p ON k.код_преподавател€ = p.код_преподавател€;