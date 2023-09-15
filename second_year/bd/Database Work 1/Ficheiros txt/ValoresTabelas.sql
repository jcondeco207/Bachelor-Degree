/*
 ___                     _       
|_ _|_ __  ___  ___ _ __| |_ ___ 
 | || '_ \/ __|/ _ \ '__| __/ __|
 | || | | \__ \  __/ |  | |_\__ \
|___|_| |_|___/\___|_|   \__|___/

*/


------------------------------------------------------------------------------------------------------------------------------------------------------------------------

--values into membro
insert into membro values ('Manel Toad' , 'somasoma@gmail.com', '1976')
insert into membro values ('Ryūnosuke Tanaka' , 'kiyoko4life@gmail.com', '1996');
insert into membro values ('Super Mario' , 'mushroom_killer@gmail.com', '1981');
insert into membro values ('Venom' , 'letalprotector@gmail.com', '2018');
insert into membro values ('Saitama' , 'one_punch_man@gmail.com', '2009');
insert into membro values ('Migi' , 'handful_person@gmail.com', '2002');
insert into membro values ('Bruce Banner' , 'gogreen@gmail.com', '1986');
insert into membro values ('Anakin Skywalker', 'idontlikesand@yahoo.com', 1999);
insert into membro values ('Sasha Braus', 'potato.girl247@gmail.com', 2002);
insert into membro values ('Agatha Harkness', 'its.been.agatha.all.along@hotmail.com', 1970)
insert into membro values ('Yelena Belova', 'notaposer@hotmail.com', 1988)
insert into membro values ('Drax', 'why.gamora@gmail.com', 1984)
insert into membro values ('Guilherme Antas', ‘they_call_me_gui@yahoo.com’, 2002);
insert into membro values ('Steven Strange', 'whatmasterdoyouserve@gmail.com', 1932);
insert into membro values ('Yukio', 'mylittleponygf@gmail.com', 1986);



------------------------------------------------------------------------------------------------------------------------------------------------------------------------


--inserts da tabela gostade (5 primeiros)
 
insert into gostade (nome , country)
select 'Manel Toad', country.name
from encompasses, country
where country.code = encompasses.country and
	  encompasses.continent = 'Europe'

insert into gostade (nome , country)
select 'Ryūnosuke Tanaka', country.name
from encompasses, country
where country.code = encompasses.country and
	  encompasses.continent = 'Europe'

insert into gostade (nome , country)
select 'Super Mario', country.name
from encompasses, country
where country.code = encompasses.country and
	  encompasses.continent = 'Europe'

insert into gostade (nome , country)
select 'Venom', country.name
from encompasses, country
where country.code = encompasses.country and
	  encompasses.continent = 'Europe'

insert into gostade (nome , country)
select 'Saitama', country.name
from encompasses, country
where country.code = encompasses.country and
	  encompasses.continent = 'Europe'

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

--inserts da tabela gostade (5 do meio)

insert into gostade (nome , country)
select 'Migi', country.name
from organization, ismember, country
where organization.abbreviation = ismember.organization and
	  ismember.country = country.code and
	  organization.name = 'European Union'

insert into gostade (nome , country)
select 'Bruce Banner', country.name
from organization, ismember, country
where organization.abbreviation = ismember.organization and
	  ismember.country = country.code and
	  organization.name = 'European Union'

insert into gostade (nome , country)
select 'Anakin Skywalker', country.name
from organization, ismember, country
where organization.abbreviation = ismember.organization and
	  ismember.country = country.code and
	  organization.name = 'European Union'

insert into gostade (nome , country)
select 'Sasha Braus', country.name
from organization, ismember, country
where organization.abbreviation = ismember.organization and
	  ismember.country = country.code and
	  organization.name = 'European Union'

insert into gostade (nome , country)
select 'Agatha Harkness', country.name
from organization, ismember, country
where organization.abbreviation = ismember.organization and
	  ismember.country = country.code and
	  organization.name = 'European Union'


------------------------------------------------------------------------------------------------------------------------------------------------------------------------

--inserts da tabela gostade (5 ultimos)

insert into gostade (nome , country)
select 'Yelena Belova', country.name
from country, language
where country.code = language.country and
      language.name = 'Portuguese' and
	  language.percentage > 0

insert into gostade (nome , country)
select 'Drax', country.name
from country, language
where country.code = language.country and
      language.name = 'Portuguese' and
	  language.percentage > 0

insert into gostade (nome , country)
select 'Guilherme Antas', country.name
from country, language
where country.code = language.country and
      language.name = 'Portuguese' and
	  language.percentage > 0

insert into gostade (nome , country)
select 'Steven Strange', country.name
from country, language
where country.code = language.country and
      language.name = 'Portuguese' and
	  language.percentage > 0

insert into gostade (nome , country)
select 'Yukio', country.name
from country, language
where country.code = language.country and
      language.name = 'Portuguese' and
	  language.percentage > 0


------------------------------------------------------------------------------------------------------------------------------------------------------------------------
