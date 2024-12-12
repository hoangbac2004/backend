insert into CLIENT_TABLE
values (0242040077, 'bac1', 'bac1');
insert into CITIZEN_IDENTIFY_CARD_TABLE
values (0242040077, 'Hoàng Văn Bắc', TO_DATE('2004-08-12', 'YYYY-MM-DD'),
        'Nam', 'Việt Nam', 'Việt Nam', 'Việt Nam', TO_DATE('2024-08-12', 'YYYY-MM-DD'));
COMMIT;


create or replace type movie as object(
    id number,
    title varchar2(1000),
    release_date date,
    rating number(3,2),
    duration number(3),
    decsription varchar2(1000)
                        );


create table movie_table of movie (
    primary key (id)
    );

insert into movie_table values (
                                1,
                                'The Shawshank Redemption',
                                TO_DATE('1994-09-23', 'YYYY-MM-DD'),
                                9.3,
                                142,
                                'hay'
                               );


insert into movie_table values (
                                2,
                                'The Godfather',
                                TO_DATE('1972-03-24', 'YYYY-MM-DD'),
                                9.2,
                                175,
                                'khong hay'
                               );

commit

