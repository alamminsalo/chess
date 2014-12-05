
create database chess;

create table Player( 
	Player_Id int not null auto_increment, 
	Player_Name varchar(64) not null, 
	Games_Total int default 0, 
	Games_Wins int default 0, 
	Games_Draws int default 0, 
	md5_Hash char(32) not null, 
	primary key (Player_Id)
);
create table Game(
	Game_Id int not null auto_increment, 
	Player_White_Id int not null, 
	Player_Black_Id int not null, 
	Turns int, 
	Winner varchar(10),
	Date date not null,
	primary key (Game_Id), 
	foreign key (Player_White_Id) references Player(Player_Id), 
	foreign key (Player_Black_Id) references Player(Player_Id)
);
create table GameMoves(
	Game_Id int not null, 
	Move varchar(8) not null, 
	Team varchar(8) not null, 
	Piece varchar(12) not null, 
	Status varchar(16),
	Turn int not null,
	foreign key (Game_Id) references Game(Game_Id)
);

insert into player (Player_Name) values ('John Doe');
insert into player (Player_Name) values ('Foo Bar');
insert into player (Player_Name) values ('Test Player');
