#version 0.0.1

#-----------news---------------------------news---------------------------news----------------

# updated to use with sqlite
# and added update cascade to foreign key constraint

#-----------news---------------------------news---------------------------news----------------

#drop database if exists dut_puc2442_proj_db;
#create database dut_puc2442_proj_db;

#use dut_puc2442_proj_db;

PRAGMA foreign_keys = ON;

create table Auteur(
	id integer primary key,
	nom varchar(30),
	prenom varchar(30)
);

create table Livre(
	id integer primary key,
	titre varchar(100),
	dateDePub datetime,
	nbreExemplairesTotal int unsigned,
	nbreExemplairesEmprunter int unsigned,
	id_auteur int unsigned,
	foreign key (id_auteur) references Auteur(id) ON UPDATE CASCADE
);

create table Adherent(
	id integer primary key,
	nom varchar(50),
	addresse varchar(100),
	nbreLivresEmprunter int unsigned
);

create table Emprunte(
	id_livre int unsigned,
	id_adherent int unsigned,
	date timestamp,
	primary key(id_livre,id_adherent,date),
	foreign key (id_livre) references Livre(id) ON UPDATE CASCADE,
	foreign key (id_adherent) references Adherent(id) ON UPDATE CASCADE
);

create table Retourne(
	id_livre int unsigned,
	id_adherent int unsigned,
	date timestamp,
	primary key(id_livre,id_adherent,date),
	foreign key (id_livre) references Livre(id) ON UPDATE CASCADE,
	foreign key (id_adherent) references Adherent(id) ON UPDATE CASCADE
);
