/*

  ___                            
 / _ \ _   _  ___ _ __ _   _ ___ 
| | | | | | |/ _ \ '__| | | / __|
| |_| | |_| |  __/ |  | |_| \__ \
 \__\_\\__,_|\___|_|   \__, |___/
                       |___/     

*/                       



-- 3 a) 

select country.name 
from organization, ismember, country
where organization.abbreviation = ismember.organization and
	  ismember.country = country.code and
	  organization.name = 'European Union';

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

-- 3 b)

select country.name
from encompasses, country
where country.code = encompasses.country and
	  encompasses.continent = 'Europe'
	  
except 

select country.name 
from organization, ismember, country
where organization.abbreviation = ismember.organization and
	  ismember.country = country.code and
	  organization.name = 'European Union';

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

-- 3 c) 

select distinct country.name, economy.gdp
from country, economy, organization, ismember
where organization.abbreviation = ismember.organization and
	  ismember.country = country.code and
	  organization.name = 'European Union' and
	  economy.country = country.code;

------------------------------------------------------------------------------------------------------------------------------------------------------------------------	  


-- 3 d)  

with values(country, n) as (select country.name, economy.gdp
					from country, economy, encompasses
					where economy.country = country.code and
						  country.code = encompasses.country and
						  encompasses.continent = 'Europe'
						)
select country 
from (select min(n) as n
	 from values) as r, values
where r.n = values.n;


------------------------------------------------------------------------------------------------------------------------------------------------------------------------

-- 3 e)

select organization.name, count(ismember.country)
from organization, ismember
where organization.abbreviation = ismember.organization
group by organization.name;



------------------------------------------------------------------------------------------------------------------------------------------------------------------------

-- 3 f)

select country.name, count(ismember.organization)
from country, ismember
where country.code = ismember.country
group by country.name;

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

-- 3 g)

with values (country, n) as (select country.name as paises, count(ismember.organization) as organizacoes
                         		 from country, ismember
                          		 where country.code = ismember.country
                          		 group by country.name)
                          
select country
from(select max(n) as n from values) as r, values
where r.n = values.n;

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

-- 3 h)

with values (org, n) as (  select organization.name, count(ismember.country)
							from organization, ismember
							where organization.abbreviation = ismember.organization
							group by organization.name)

select org
from (select min(n) as n from values) as r, list
where r.n = list.n;

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

-- 3 i)

with value(country, n) as ( select country.name, economy.gdp
                         	from country, economy
                          	where country.code = economy.country 
)
            
select country
from(select max(n) as n from data) as d, data
where d.n = data.n;



------------------------------------------------------------------------------------------------------------------------------------------------------------------------

-- 3 j)

   select name
   from  country as c
   where not exists (select organization.name 
	  				from organization, ismember, country
					where organization.abbreviation = ismember.organization and
				          ismember.country = country.code and
						  country.name = 'Morocco'
                    except
                    select organization.name
                    from organization, ismember
                    where organization.abbreviation = ismember.organization and
					      ismember.country = c.code );



------------------------------------------------------------------------------------------------------------------------------------------------------------------------

--3 k)

select name
from organization as o
where not exists(
				 select country.name 
				 from country, ismember
				 where country.code = ismember.country and
				 ismember.organization = 'Benelux'
				 except
				 select country.name 
				 from country, ismember
				 where country.code = ismember.country and
				 ismember.organization = o.abbreviation
				 );

























