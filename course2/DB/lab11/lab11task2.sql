declare curs cursor local                            
for SELECT SUBJECT_NAME, PULPIT from SUBJECT;
declare @subj char(50), @pulpit char(50);      
open curs;	  
fetch  curs into @subj, @pulpit; 	
print '1. '+@subj+ @pulpit;   
go
declare @subj char(50), @pulpit char(50);     	
fetch  curs into @subj, @pulpit; 	
print '2. '+@subj+ @pulpit;  
go


declare mycurs cursor global
for select SUBJECT_NAME, PULPIT from SUBJECT
declare @subj char(50), @pulpit char(50)
open mycurs
fetch mycurs into @subj, @pulpit
print '1. '+@subj+ @pulpit;   
go
declare @subj char(50), @pulpit char(50);     	
fetch  mycurs into @subj, @pulpit; 	
print '2. '+@subj+ @pulpit;  
close mycurs
deallocate mycurs
go


