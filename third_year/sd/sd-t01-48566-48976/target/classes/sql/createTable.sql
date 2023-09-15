create table ads(   location char(100),
                    price real,
                    gender char(40),
                    date char(60),
                    advertiser char(60),
                    typology char(60),
                    type char(60),
                    state boolean,
                    aid integer,
                    PRIMARY KEY (aid));

create table messages(  aid integer,
                        sender varchar,
                        msg varchar,
                        FOREIGN key(aid) references ads(aid));


create table users(     username varchar,
                        password varchar,
                        type integer, -- 0 -> cliente | 1 -> gestor
                        alias varchar,
                        PRIMARY KEY (username));

create table userAds(   username varchar,
                        aid integer,
                        FOREIGN KEY (username) references users(username),
                        FOREIGN KEY (aid) references ads(aid));

create table userMsg(   username varchar,
                        sender varchar,
                        msg varchar,
                        FOREIGN KEY (username) references users(username));


