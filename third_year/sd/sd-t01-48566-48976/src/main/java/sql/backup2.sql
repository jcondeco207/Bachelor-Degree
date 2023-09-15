--
-- PostgreSQL database dump
--

-- Dumped from database version 14.5 (Homebrew)
-- Dumped by pg_dump version 14.5 (Homebrew)

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- Name: ads; Type: TABLE; Schema: public; Owner: jrcondeco
--

CREATE TABLE public.ads (
    location character(100),
    price real,
    gender character(40),
    date character(60),
    advertiser character(60),
    typology character(60),
    type character(60),
    state boolean,
    aid integer NOT NULL
);


ALTER TABLE public.ads OWNER TO jrcondeco;

--
-- Name: messages; Type: TABLE; Schema: public; Owner: jrcondeco
--

CREATE TABLE public.messages (
    aid integer,
    sender character varying,
    msg character varying
);


ALTER TABLE public.messages OWNER TO jrcondeco;

--
-- Name: userads; Type: TABLE; Schema: public; Owner: jrcondeco
--

CREATE TABLE public.userads (
    username character varying,
    aid integer
);


ALTER TABLE public.userads OWNER TO jrcondeco;

--
-- Name: usermsg; Type: TABLE; Schema: public; Owner: jrcondeco
--

CREATE TABLE public.usermsg (
    username character varying,
    sender character varying,
    msg character varying
);


ALTER TABLE public.usermsg OWNER TO jrcondeco;

--
-- Name: users; Type: TABLE; Schema: public; Owner: jrcondeco
--

CREATE TABLE public.users (
    username character varying NOT NULL,
    password character varying,
    type integer,
    alias character varying
);


ALTER TABLE public.users OWNER TO jrcondeco;

--
-- Data for Name: ads; Type: TABLE DATA; Schema: public; Owner: jrcondeco
--

COPY public.ads (location, price, gender, date, advertiser, typology, type, state, aid) FROM stdin;
Stark Industries                                                                                    	9000	masculino                               	2022-01-05                                                  	Tony Stark                                                  	T4                                                          	procura                                                     	f	3
Bacelo, Évora                                                                                       	400	masculino                               	2022-11-22                                                  	Mário Josias                                                	T2                                                          	oferta                                                      	f	24
Queens, New York                                                                                    	500	indiferente                             	2022-11-22                                                  	Ivan Ditkovich                                              	T1                                                          	oferta                                                      	t	20
Mos Eisley, Tatooine                                                                                	1000	indiferente                             	2022-11-22                                                  	Anakin Skywalker                                            	T5                                                          	procura                                                     	t	21
Centro histórico, Évora                                                                             	200	feminino                                	2022-11-22                                                  	Miguel Oliveira                                             	T4                                                          	oferta                                                      	t	22
Centro histórico, Évora                                                                             	100	feminino                                	2022-11-22                                                  	Maria João                                                  	T0                                                          	procura                                                     	t	23
Queens, New York                                                                                    	500	indiferente                             	2022-11-22                                                  	Peter Parker                                                	T1                                                          	procura                                                     	t	25
Centro de Lisboa                                                                                    	300	indiferente                             	2022-11-20                                                  	João Condeço                                                	T4                                                          	oferta                                                      	t	19
\.


--
-- Data for Name: messages; Type: TABLE DATA; Schema: public; Owner: jrcondeco
--

COPY public.messages (aid, sender, msg) FROM stdin;
22	Maria João	É possível reduzir o preço?
22	Miguel Oliveira	sure.
\.


--
-- Data for Name: userads; Type: TABLE DATA; Schema: public; Owner: jrcondeco
--

COPY public.userads (username, aid) FROM stdin;
\.


--
-- Data for Name: usermsg; Type: TABLE DATA; Schema: public; Owner: jrcondeco
--

COPY public.usermsg (username, sender, msg) FROM stdin;
spidey	Ivan Ditkovich	give me rent
spidey	Ivan Ditkovich	Listen this is a free country, not a rent-free country...
giveMeRent	Peter Parker	You will get your rent when you fix this damn door!
chad2002	Maria João	É possível reduzir o preço?
chad2002	Miguel Oliveira	sure.
\.


--
-- Data for Name: users; Type: TABLE DATA; Schema: public; Owner: jrcondeco
--

COPY public.users (username, password, type, alias) FROM stdin;
jsaias	76c32a7fe9bfa4dc88916c2f008dd69f	0	José Saias
jrcondeco	20ef7a2f9fc76039ebd837de2fbc00cf	1	João Condeço
jcarrasqueira	c3948f0d30ae46dbe4accafd392b3e46	1	Joana Carrasqueira
somasToad	fda68308a0c10087ffe5c3ce65ef6c40	0	Mário Josias
chosenOne	bf0858eab5fcb9f25265efd40f24495a	0	Anakin Skywalker
chad2002	b405751a7e7abb97f453246caa86cbb4	0	Miguel Oliveira
artsStudent20	f8c932c0bd48bb309d3dbd120bf5d5c0	0	Maria João
giveMeRent	e15edd79fd63c7887fea0d40de3c0fff	0	Ivan Ditkovich
spidey	37801e2fb4e47403890f53c077d697f3	0	Peter Parker
\.


--
-- Name: ads ads_pkey; Type: CONSTRAINT; Schema: public; Owner: jrcondeco
--

ALTER TABLE ONLY public.ads
    ADD CONSTRAINT ads_pkey PRIMARY KEY (aid);


--
-- Name: users users_pkey; Type: CONSTRAINT; Schema: public; Owner: jrcondeco
--

ALTER TABLE ONLY public.users
    ADD CONSTRAINT users_pkey PRIMARY KEY (username);


--
-- Name: messages messages_aid_fkey; Type: FK CONSTRAINT; Schema: public; Owner: jrcondeco
--

ALTER TABLE ONLY public.messages
    ADD CONSTRAINT messages_aid_fkey FOREIGN KEY (aid) REFERENCES public.ads(aid);


--
-- Name: userads userads_aid_fkey; Type: FK CONSTRAINT; Schema: public; Owner: jrcondeco
--

ALTER TABLE ONLY public.userads
    ADD CONSTRAINT userads_aid_fkey FOREIGN KEY (aid) REFERENCES public.ads(aid);


--
-- Name: userads userads_username_fkey; Type: FK CONSTRAINT; Schema: public; Owner: jrcondeco
--

ALTER TABLE ONLY public.userads
    ADD CONSTRAINT userads_username_fkey FOREIGN KEY (username) REFERENCES public.users(username);


--
-- Name: usermsg usermsg_username_fkey; Type: FK CONSTRAINT; Schema: public; Owner: jrcondeco
--

ALTER TABLE ONLY public.usermsg
    ADD CONSTRAINT usermsg_username_fkey FOREIGN KEY (username) REFERENCES public.users(username);


--
-- PostgreSQL database dump complete
--

