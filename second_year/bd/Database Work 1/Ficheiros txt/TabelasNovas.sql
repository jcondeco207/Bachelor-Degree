/*
 _____     _          _           
|_   _|_ _| |__   ___| | __ _ ___ 
  | |/ _` | '_ \ / _ \ |/ _` / __|
  | | (_| | |_) |  __/ | (_| \__ \
  |_|\__,_|_.__/ \___|_|\__,_|___/
  
*/


--Criar as tabelas

-- Create Membro

create table membro(
  				nome char(40),
  				email char(40),
  				ano integer,
  				PRIMARY key(nome))
				
-- Create gostaDe

create table gostaDe(
  				nome char(40),
  				country char(30),
  				FOREIGN key(nome) references membro(nome),
  				FOREIGN key(country) references country(name)
  				)
				





