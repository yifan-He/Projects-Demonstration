use
ijc353_1;

create table Person
(
    SSN               int primary key,
    medicalCardNumber int unique,
    firstName         varchar(20)  not null,
    lastName          varchar(20)  not null,
    birthDate         date         not null,
    telephone         varchar(30),
    address           varchar(300) not null,
    city              varchar(20)  not null,
    province          varchar(30)  not null,
    postalCode        varchar(30)  not null,
    citizenship       varchar(50)  not null,
    email             varchar(100)
);

create table AgeGroup
(
    ageGroupNumber int primary key not null auto_increment,
    fromAge        int             not null,
    toAge          int             not null
);

create table Vaccine
(
    vaccineId      int primary key,
    vaccineType    varchar(50),
    approvalDate   date,
    vaccineStatus  varchar(20) check (vaccineStatus = 'SAFE' or vaccineStatus = 'SUSPENDED'),
    suspensionDate date
);

create table Facility
(
    facilityName varchar(100) primary key,
    address      varchar(300) not null,
    city         varchar(20)  not null,
    province     varchar(30)  not null,
    postalCode   varchar(30)  not null,
    phone        varchar(30),
    webAddress   varchar(100),
    facilityType varchar(30) check (facilityType = 'clinic' or facilityType = 'hospital' or
                                    facilityType = 'special installment')
);

create table Inventory
(
    shipmentNumber int primary key,
    vaccineType    varchar(30),
    amount         int not null default 0
);

create table HealthWorker
(
    employeeId        int primary key,
    SSN               int unique   not null,
    firstName         varchar(20)  not null,
    lastName          varchar(20)  not null,
    birthDate         date         not null,
    medicalCardNumber int unique   not null,
    telephone         varchar(30),
    address           varchar(300) not null,
    city              varchar(20)  not null,
    province          varchar(30)  not null,
    postalCode        varchar(30)  not null,
    citizenship       varchar(50)  not null,
    email             varchar(100),
    startDate         date         not null,
    endDate           date
);

create table Infection
(
    infectionType varchar(20) default 'UNKNOWN' primary key
);

create table PersonOf
(
    SSN           int,
    infectionType varchar(20) default 'UNKNOWN',
    infectionDate date,
    primary key (SSN, InfectionType),
    foreign key (SSN) references Person (SSN)
);

create table BelongTo
(
    SSN            int primary key,
    ageGroupNumber int,
    foreign key (SSN) references Person (SSN),
    foreign key (ageGroupNumber) references AgeGroup (ageGroupNumber)
);

create table Vaccination
(
    SSN             int,
    vaccineId       int,
    facilityName    varchar(100),
    doseNumber      int,
    vaccinationDate date,
    primary key (SSN, vaccineId, facilityName),
    foreign key (SSN) references Person (SSN),
    foreign key (vaccineId) references Vaccine (vaccineId),
    foreign key (facilityName) references Facility (facilityName)
);

create table Receive
(
    shipmentNumber int,
    facilityName   varchar(100),
    receptionDate  date,
    primary key (shipmentNumber, facilityName),
    foreign key (shipmentNumber) references Inventory (shipmentNumber),
    foreign key (facilityName) references Facility (facilityName)
);

create table TransferFrom
(
    shipmentNumber int,
    facilityName   varchar(100),
    primary key (shipmentNumber, facilityName),
    foreign key (shipmentNumber) references Inventory (shipmentNumber),
    foreign key (facilityName) references Facility (facilityName)
);

create table TransferTo
(
    shipmentNumber int,
    facilityName   varchar(100),
    primary key (shipmentNumber, facilityName),
    foreign key (shipmentNumber) references Inventory (shipmentNumber),
    foreign key (facilityName) references Facility (facilityName)
);

create table Manage
(
    facilityName varchar(100) primary key,
    employeeId   int,
    foreign key (employeeId) references HealthWorker (employeeId),
    foreign key (facilityName) references Facility (facilityName)
);

create table Work
(
    employeeId   int,
    facilityName varchar(100),
    primary key (employeeId, facilityName),
    foreign key (employeeId) references HealthWorker (employeeId),
    foreign key (facilityName) references Facility (facilityName)
);

insert into Person
values(1,1234,'gechen','Ma','1936-02-03','5111234546','1411 du fort','Montreal','quebec','h3h2n8','Canada','magechen2016@hotmail.com');
insert into Person
values(2,1235,'fengyan','liu','1946-02-03',5141234456,'1406 du fort','Montreal','quebec','h3h2n8','Canada','444@hotmail.com');
insert into Person
values(3,1236,'yu','xiao','1956-02-03',5145554444,'1408 du fort','Montreal','quebec','h3h2n8','Canada','yuxiao2016@hotmail.com');
insert into Person
values(678,null,'han','zuo','1966-02-03',5145366666,'1411 du fort','Montreal','quebec','h3h2n8','China','zuohan2016@hotmail.com');
insert into Person
values(789,null,'ziting','zhou','1976-02-03',5141112222,'1400 du fort','Montreal','quebec','h3h2x8','Korea','ziting2016@hotmail.com');
insert into Person
values(5,12337,'lebron','James','1976-02-03',5141112222,'1400 du fort','Montreal','quebec','h3h2x8','Korea','efdsfdsaf2016@hotmail.com');
insert into Person
values(9,12338,'li','yao','1986-02-03', '5142223333','1445 du fort','Montreal','quebec','h3h2a8','Canada','yaoli2016@hotmail.com');
insert into Person
values(10,12339,'yutao','Meng','1996-02-03', '5143334444','1234 du fort','Montreal','quebec','h1g2n8','canada','yutao2016@hotmail.com');
insert into Person
values(11,12340,'ke','Ma','2006-02-03', '5144445555','1456 du fort','Montreal','quebec','h3h2n7','Canada','kema2016@hotmail.com');
insert into Person
values(12,12341,'zhiyang','deng','2016-02-03', '5145556666','1200 du fort','Toronto','Ontario','h1h3n8','Canada','zhiyang2016@hotmail.com');
insert into Person
values(13,12342,'junqiao','huang','2020-02-03', '5146667777','1234 du fort','Montreal','quebec','h1h2x8','Canada','junqiao2016@hotmail.com');
insert into Person
values(14,12343,'bob','Lee','2020-02-01', '5146669999','1234 du fort','Montreal','quebec','h1h2x8','Canada','Lee2016@hotmail.com');
insert into Person
values(15,12344,'Alan','Zhang','2020-04-03', '5146668888','1234 du fort','Montreal','quebec','h1h2x8','Canada','zhang2016@hotmail.com');
insert into Person
values(16,12345,'guodong','Liu','2020-08-03', '5146668790','1234 du fort','Montreal','quebec','h1h2x8','Canada','guodong123@hotmail.com');
insert into Person
values(17,12346,'junqiao','He','2020-02-03', '51466687654','1200 du fort','Montreal','quebec','h1h2x3','Canada','baby@hotmail.com');

insert into AgeGroup
values (1, 80, 120);
insert into AgeGroup
values (2, 70, 79);
insert into AgeGroup
values (3, 60, 69);
insert into AgeGroup
values (4, 50, 59);
insert into AgeGroup
values (5, 40, 49);
insert into AgeGroup
values (6, 30, 39);
insert into AgeGroup
values (7, 18, 29);
insert into AgeGroup
values (8, 12, 17);
insert into AgeGroup
values (9, 5, 11);
insert into AgeGroup
values (10, 0, 4);

insert into Vaccine
values(111,'Pfizer','2020-12-20','SAFE',null);
insert into Vaccine
values(112,'Pfizer','2020-12-20','SAFE',null);
insert into Vaccine
values(222,'Moderna','2020-10-21','SAFE',null);
insert into Vaccine
values(223,'Moderna','2020-10-21','SUSPENDED','2020-12-20');
insert into Vaccine
values(333,'AstraZeneca','2020-11-01','SAFE',null);
insert into Vaccine
values(334,'AstraZeneca','2020-12-01','SAFE',null);
insert into Vaccine
values(335,'AstraZeneca','2021-02-01','SAFE',null);
insert into Vaccine
values(336,'AstraZeneca','2020-10-01','SAFE',null);
insert into Vaccine
values(444,'Johnson&Johnson','2020-12-20','SUSPENDED','2021-02-03');
insert into Vaccine
values(445,'Johnson&Johnson','2020-11-25','SAFE',null);
insert into Vaccine
values(113,'Pfizer','2020-12-20','SAFE',null);
insert into Vaccine
values(114,'Pfizer','2020-12-20','SAFE',null);
insert into Vaccine
values(337,'AstraZeneca','2020-11-01','SAFE',null);
insert into Vaccine
values(338,'AstraZeneca','2020-12-01','SAFE',null);



insert into Facility
values ('CLSC Montreal South', '11441 Lacordaire', 'Montreal', 'Quebec', '1n1n1', '5143842000',
        'https://www.ciusssnordmtl.ca/installations/clsc/clsc-de-montreal-nord/', 'clinic');
insert into Facility
values ('Olympic Stadium Montreal', '4545 Pierre-de Coubertin Ave', 'Montreal', 'Quebec', '1n1n0', '514438222',
        'https://parcolympique.qc.ca/en/what-to-do/olympic-stadium/', 'special installment');
insert into Facility
values ('Clinique Santé 24/7', '2046 Mont-Royal Ave E', 'Montreal', 'Quebec', '1n1n2', '5148192247',
        'https://expertise24-7.com/clinique/services', 'clinic');
insert into Facility
values ('1234 clinic', '11441 Lacordaire', 'Toronto', 'Ontario', '1n1n1', '5143842000',
        'https://www.1234clinic.ca/installations/clsc/clsc-de-montreal-nord/', 'clinic');
insert into Facility
values ('Clinique de vaccination dAhuntsic', '800 Boul Henri-Bourassa o', 'Montreal', 'Quebec', 'H3L 1P5', '4382238562',
        'https://santemontreal.qc.ca/en/public/coronavirus-covid-19/vaccination/vaccination-sites/#c51195', 'clinic');

insert into HealthWorker
values(12339,9,'li','yao','1986-02-03',12338, '5142223333','1445 du fort','Montreal','quebec','h3h2a8','Canada','yaoli2016@hotmail.com','2020-07-14', '2021-02-14');
insert into HealthWorker
values(12340,10,'yutao','Meng','1996-02-03',12339, '5143334444','1234 du fort','Montreal','quebec','h1g2n8','Canada','yutao2016@hotmail.com','2020-10-18', null);
insert into HealthWorker
values(12341,11,'ke','Ma','2006-02-03',12340, '5144445555','1456 du fort','Montreal','quebec','h3h2n7','canada','kema2016@hotmail.com', '2020-09-18',null);
insert into HealthWorker
values(12342,12,'zhiyang','deng','2016-02-03',12341, '5145556666','1200 du fort','Montreal','quebec','h1h3n8','Canada','zhiyang2016@hotmail.com','2020-02-03', '2020-10-19');
insert into HealthWorker
values(12343,3,'yu','xiao','1956-02-03',1236,5145554444,'1408 du fort','Montreal','quebec','h3h2n8','Canada','yuxiao2016@hotmail.com', '2020-01-18', '2021-02-18');
insert into HealthWorker
values(12344,6,'li','yao','1986-02-03',12337, '5142223333','1445 du fort','Montreal','quebec','h3h2a8','Canada','yaoli2016@hotmail.com','2021-04-14', '2021-07-14');

insert into Inventory
values(1001,'Moderna',20);
insert into Inventory
values(4567,'Moderna',100);
insert into Inventory
values(4568,'AstraZeneca',50);
insert into Inventory
values(4569,'Johnson&Johnson',20);
insert into Inventory
values(1003,'Moderna',10);
insert into Inventory
values(4570,'Moderna',20);
insert into Inventory
values(4571,'Johnson&Johnson',150);
insert into Inventory
values(4572,'Johnson&Johnson',100);
insert into Inventory
values(4573,'Johnson&Johnson',50);
insert into Inventory
values(1004,'Johnson&Johnson',20);
insert into Inventory
values(1005,'Johnson&Johnson',10);
insert into Inventory
values(1006,'Moderna',10);
insert into Inventory
values(4574,'Pfizer',50);

insert into Infection
values ('Alpha');
insert into Infection
values ('beta');
insert into Infection
values ('Gamma');
insert into Infection
values ('delta');

insert into PersonOf
values(1,'Alpha','2020-01-24');
insert into PersonOf
values(2,'Delta','2020-10-05');
insert into PersonOf
values(3,'beta','2020-09-24');
insert into PersonOf
values(3,'Alpha','2020-10-24');
insert into PersonOf
values(2,'Alpha','2021-01-24');
insert into PersonOf
values(13,'Alpha','2020-09-24');

insert into BelongTo
values(1,1);
insert into BelongTo
values(2,2);
insert into BelongTo
values(3,3);
insert into BelongTo
values(678,3);
insert into BelongTo
values(789,4);
insert into BelongTo
Values(13,10);
insert into BelongTo
Values(5,5);
insert into BelongTo
Values(9,6);
insert into BelongTo
Values(10,7);
insert into BelongTo
Values(11,8);
insert into BelongTo
Values(12,9);
insert into BelongTo
Values(14,10);
insert into BelongTo
Values(15,10);
insert into BelongTo
Values(16,10);
insert into BelongTo
Values(17,10);

insert into Vaccination
values(1,111,'CLSC Montreal South',1,'2021-02-03');
insert into Vaccination
values(1,112,'CLSC Montreal South',2,'2021-06-03');
insert into Vaccination
values(2,222,'Olympic Stadium Montreal',1,'2021-03-03');
insert into Vaccination
values(3,333,'Olympic Stadium Montreal',1,'2021-02-06');
insert into Vaccination
values(3,223,'CLSC Montreal South',2,'2021-06-03');
insert into Vaccination
values(678,334,'CLSC Montreal South',1,'2021-03-01');
insert into Vaccination
values(10,445,'CLSC Montreal South',1,'2021-06-03');
insert into Vaccination
values(10,335,'CLSC Montreal South',2,'2021-07-29');
insert into Vaccination
values(13,336,'CLSC Montreal South',1,'2020-11-03');
#这四个人打不了。。。
insert into Vaccination
values(14,113,'CLSC Montreal South',1,'2020-11-03');
insert into Vaccination
values(15,114,'CLSC Montreal South',1,'2020-10-03');
insert into Vaccination
values(16,337,'CLSC Montreal South',1,'2021-01-03');
insert into Vaccination
values(17,338,'CLSC Montreal South',1,'2021-03-03');


insert into Receive
values(4567, 'CLSC Montreal South','2021-02-03');
insert into Receive
values(4568, 'Olympic Stadium Montreal','2021-03-03');
insert into Receive
values(4569, 'Clinique Santé 24/7','2021-04-03');
insert into Receive
values(4570, 'Olympic Stadium Montreal','2021-02-03');
insert into Receive
values(4571, '1234 clinic','2021-04-03');
insert into Receive
values(4572, 'CLSC Montreal South','2021-06-03');
insert into Receive
values(4573, 'Olympic Stadium Montreal','2021-03-03');
#同样，我有4574但就是receive 不了
insert into Receive
values(4574, 'Olympic Stadium Montreal','2021-02-03');

insert into TransferFrom
values(1001,'CLSC Montreal South');
insert into TransferFrom
values(1003,'CLSC Montreal South');
insert into TransferFrom
values(1004,'Olympic Stadium Montreal');
insert into TransferFrom
values(1005,'Olympic Stadium Montreal');
insert into TransferFrom
values(1006,'CLSC Montreal South');

insert into TransferTo
values(1001,'Clinique Santé 24/7');
insert into TransferTo
values(1003,'Clinique de vaccination dAhuntsic');
insert into TransferTo
values(1004,'Clinique de vaccination dAhuntsic');
insert into TransferTo
values(1005,'CLSC Montreal South');
insert into TransferTo
values(1006,'Clinique Santé 24/7');

insert into Manage
values ('CLSC Montreal South', 12339);

insert into Work
values(12339,'CLSC Montreal South');
insert into Work
values(12340,'CLSC Montreal South');
insert into Work
values(12341,'CLSC Montreal South');
insert into Work
values(12342,'CLSC Montreal South');
insert into Work
values(12343,'Olympic Stadium Montreal');
insert into Work
values(12344,'CLSC Montreal South');

#----------------------------------------------------------------------------------------------------
#Q1:
#1.1create a person：
insert into Person
values(4,1111,'Chris','Paul','1936-02-03','5111121234','1412 du fort','Montreal','quebec','h3h2n4','Canada','magechen2016@hotmail.com');
insert into PersonOf
values(4,'Alpha','2021-01-21');

#1.2 delete a person:
delete from PersonOf where SSN=4;
delete from Person where SSN=4;

#1.3 Edit a person:
update Person
set firstName='James'
where SSN=4;

#1.4 Display a person
select *
from Person, PersonOf
where Person.SSN=4 and PersonOf.SSN=Person.SSN;

#Q2:
select * from HealthWorker;
#2.1create a health worker：
insert into HealthWorker
values(123333,18,'Allen','Iverson','1987-02-13',2350, '5142223332','1460 du fort','Montreal','quebec','h3h2a8','Canada','yaoli2016@hotmail.com','2020-03-14', null);
#2.2 delete a health worker:
delete from HealthWorker where employeeID=123333;

#2.3 Edit a health worker:
update HealthWorker
set telephone='5145761122'
where employeeID=123333;

#2.4 Display a person
select * from HealthWorker where employeeID=123333;

#Q3:
#3.1create a public health facility：
insert into Facility
values('1101 clinic','10011 Lacordaire','Montreal','Quebec','1n1n1','5143842000','https://www.1001Clinic.ca/installations/clsc/clsc-de-montreal-nord/','clinic');

#3.2 delete a public health facility：
delete from Facility where facilityName='1101 clinic';

#3.3 Edit a public health facility：
update Facility
set phone='5145761233'
where facilityName='1101 clinic';

#3.4 Display a public health facility：
select * from Facility where facilityName='1101 clinic';

#Q4:
#4.1create a vaccination type：
insert into Vaccine
values(188,'Pfizer','2020-10-20','SAFE',null);

#4.2 delete a vaccination type：
delete from Vaccine where VaccineId=188;

#4.3 Edit a public vaccine type：
update Vaccine
set approvalDate='2020-10-01'
where vaccineId=188;

#4.4 Display a vaccine type：
select * from Vaccine where vaccineId=188 ;

#Q5:
#5.1create a infectioin variant type：
insert into Infection
values('lamda');

#5.2 delete a infectioin variant type：
delete from Infection where infectionType='lamda';

#5.3 Edit a infectioin variant type：
update Infection
set infectionType='Delta plus'
where infectionType='lamda';

#5.4 Display a vaccine type：
select * from Infection where infectionType='Delta plus' ;

#Q6:
#6.1create a group age ：
insert into AgeGroup
values(11,120,140);

#6.2 delete a group age ：
delete from AgeGroup where ageGroupNumber=11;

#6.3 Edit a group age ：
update AgeGroup
set toAge=150
where ageGroupNumber=11;

#6.4 Display a group age：
select * from AgeGroup where ageGroupNumber=11 ;

#Q7:
#7.1 add a province  ：
alter table AgeGroup add province varchar(20) unique;

#7.2 delete a group age ：
alter table AgeGroup drop province;

#Q8:
#8.1 set a new age group for province:
update AgeGroup
set province='Quebec'
where ageGroupNumber=3;

#Q9:
select Receive.shipmentNumber, Receive.receptionDate,Receive.FacilityName,Inventory.amount,Inventory.vaccineType
from inventory,Receive
where Receive.shipmentNumber=inventory.shipmentNumber;

#Q10:
select TransferFrom.shipmentNumber,TransferFrom.facilityName,TransferTo.facilityName,Inventory.vaccineType,Inventory.amount
From TransferFrom,TransferTo,Inventory
where TransferFrom.shipmentNumber=TransferTo.shipmentNumber and TransferTo.shipmentNumber=Inventory.shipmentNumber;

#q12:
SELECT  Person.lastName, Person.firstName, Person.birthdate,  Person.email,  Person.telephone,  Person.city,  Vaccination.vaccinationDate,  Vaccine.vaccineType,
        if((Person.SSN not in(select PersonOf.SSN from PersonOf))=true,'no','yes') as infectionStatus
FROM person, belongto, agegroup, vaccination, vaccine
WHERE BelongTo.ageGroupNumber =10 AND Person.SSN = belongto.SSN and BelongTo.ageGroupNumber=AgeGroup.ageGroupNumber
  AND Vaccination.doseNumber = 1
  AND Vaccination.vaccineId = Vaccine.vaccineId AND Person.SSN = vaccination.SSN;

#q13:
SELECT  Person.firstName, Person.lastName, Person.birthDate, Person.email, Person.telephone, Person.city, Vaccination.vaccinationDate, Vaccine.vaccineType,
        if((Person.SSN not in(select PersonOf.SSN from PersonOf))=true,'no','yes') as infectionStatus
FROM Person,vaccination, vaccine,
     (SELECT Person.SSN, COUNT(Vaccination.vaccineId) AS NUM
      FROM Person , Vaccination, Vaccine
      WHERE Person.SSN = Vaccination.SSN AND Vaccine.vaccineId = Vaccination.vaccineId
      GROUP BY Person.SSN) AS TEMP
WHERE Person.SSN = TEMP.SSN AND TEMP.NUM >= 2 AND vaccination.vaccineId = vaccine.vaccineId AND person.SSN = vaccination.SSN;

#q14
SELECT distinct Person.firstName, Person.lastName, Person.birthDate, Person.email, Person.telephone, Person.city, Vaccination.vaccinationDate, Vaccine.vaccineType, Vaccination.doseNumber,
                if((Person.SSN not in(select PersonOf.SSN from PersonOf))=true,'no','yes') as infectionStatus
FROM Person, Vaccination, Vaccine, PersonOf, (select distinct PersonOf.SSN,count(PersonOf.SSN) as infectionNumber from PersonOf group by PersonOf.SSN) as temp
where Vaccination.doseNumber >=1 and temp.infectionNumber>=2
  and Person.SSN=PersonOf.SSN and Person.SSN=Vaccination.SSN and Vaccination.VaccineId=Vaccine.vaccineId
  and Person.SSN=temp.SSN and temp.SSN=Vaccination.SSN;

#q15:
select Facility.province,Inventory.vaccineType,sum(Inventory.amount) as vaccineAmount
from Facility,Inventory,Receive
where Inventory.shipmentNumber=Receive.shipmentNumber and Facility.facilityName=Receive.facilityName
group by  Facility.province,Inventory.vaccineType
order by Facility.province asc,vaccineAmount desc;

#q16:
select   Person.province,Vaccine.vaccineType, count(distinct temp.SSN) as numberOfPeople
from Person,Vaccine,Vaccination, (select Vaccination.SSN,vaccineId, count(Vaccination.VaccineId) as a from Vaccination group by Vaccination.SSN,vaccineId) as temp
where Person.SSN=Vaccination.SSN and Vaccination.vaccineId=Vaccine.vaccineId and temp.SSN=Vaccination.SSN and Vaccination.vaccinationDate>'2021-01-01' and Vaccination.vaccinationDate<'2021-07-22'
group by Person.Province,Vaccine.vaccineType;

#Q17:
select Facility.city,sum(Inventory.amount) as vaccineAmount
from Facility,Inventory,Receive
where Facility.province='Quebec' and Receive.shipmentNumber=Inventory.shipmentNumber
  and Facility.facilityName=Receive.facilityName and Receive.receptionDate>'2021-01-01' and Receive.receptionDate<'2021-07-22'
group by Facility.city;

#Q18
#all facility and workers
select Facility.facilityName,Facility.address,Facility.facilityType,Facility.phone,
       count(HealthWorker.employeeId)
from Facility,Work,HealthWorker
where Facility.city='Montreal' and Work.facilityName=Facility.facilityName and Work.employeeId=HealthWorker.employeeId
group by Facility.facilityName;

#total transferｓ
select Facility.facilityName, sum(temp.numberOfDose) as totalTransfer
from Facility,
     ((select Facility.facilityName as a, count(TransferFrom.shipmentNumber) as numberOfShipment , sum(Inventory.amount) as numberOfDose
       from Facility,Inventory, TransferFrom
       where Facility.city='Montreal' and Inventory.shipmentNumber=TransferFrom.shipmentNumber and TransferFrom.facilityName=Facility.facilityName
       group by Facility.facilityName) union
      (select Facility.facilityName as a, count(TransferTo.shipmentNumber) as numberOfShipment , sum(Inventory.amount) as numberOfDose
       from Facility,Inventory, TransferTo
       where Facility.city='Montreal' and Inventory.shipmentNumber=TransferTo.shipmentNumber and TransferTo.facilityName=Facility.facilityName
       group by Facility.facilityName
      ) ) as Temp
where Facility.facilityName=Temp.a
group by Facility.facilityName;

#receive
select Facility.facilityName, count(Receive.shipmentNumber) as numberOfShipment, sum(Inventory.amount) as numberOfDose
from Facility,Inventory, Receive
where Facility.city='Montreal' and Inventory.shipmentNumber=Receive.shipmentNumber and Receive.facilityName=Facility.facilityName
group by Facility.facilityName;

#Transfer to
select Facility.facilityName, count(TransferTo.shipmentNumber) as numberOfShipment , sum(Inventory.amount) as numberOfDose
from Facility,Inventory, TransferTo
where Facility.city='Montreal' and Inventory.shipmentNumber=TransferTo.shipmentNumber and TransferTo.facilityName=Facility.facilityName
group by Facility.facilityName;

#transferFrom
select Facility.facilityName, count(TransferFrom.shipmentNumber) as numberOfShipment , sum(Inventory.amount) as numberOfDose
from Facility,Inventory, TransferFrom
where Facility.city='Montreal' and Inventory.shipmentNumber=TransferFrom.shipmentNumber and TransferFrom.facilityName=Facility.facilityName
group by Facility.facilityName;

#vaccine of each facility
select Facility.facilityName,Vaccine.vaccineType,(Rece.numberOfDose+transT.numberOfDose-transF.numberofDose) as totalVaccine
from Facility,Vaccine,
     (select Facility.facilityName as a, Inventory.vaccineType as b , sum(Inventory.amount) as numberOfDose
      from Facility,Inventory, TransferFrom
      where Facility.city='Montreal' and Inventory.shipmentNumber=TransferFrom.shipmentNumber and TransferFrom.facilityName=Facility.facilityName
      group by Facility.facilityName,Inventory.vaccineType) as transF,
     (select Facility.facilityName as a,  Inventory.vaccineType as b , sum(Inventory.amount) as numberOfDose
      from Facility,Inventory, TransferTo
      where Facility.city='Montreal' and Inventory.shipmentNumber=TransferTo.shipmentNumber and TransferTo.facilityName=Facility.facilityName
      group by Facility.facilityName,Inventory.vaccineType
     ) as transT,
     (select Facility.facilityName as a,  Inventory.vaccineType as b, sum(Inventory.amount) as numberOfDose
      from Facility,Inventory, Receive
      where Facility.city='Montreal' and Inventory.shipmentNumber=Receive.shipmentNumber and Receive.facilityName=Facility.facilityName
      group by Facility.facilityName,Inventory.vaccineType) as Rece
where  (Facility.facilityName=transF.a or  Facility.facilityName=transT.a or  Facility.facilityName=Rece.a)
  and  (Vaccine.vaccineType=transF.b or Vaccine.vaccineType=transT.b or Vaccine.vaccineType=Rece.b)
  and (transF.a=transT.a  or  transF.a=Rece.a or transT.a=Rece.a)
  and (transF.b=transT.b or transF.b=Rece.b or transT.b=Rece.b);

#the number of people vaccinated in the facility
select Facility.facilityName, count(distinct Vaccination.SSN) as peopleVaccineIn ,count(Vaccination.SSN) peopleDoseIn
from Facility,Vaccination,Vaccine
where Vaccination.vaccineId=Vaccine.vaccineId and Vaccination.facilityName=Facility.facilityName
group by Facility.facilityName;

#q19
select HealthWorker.employeeId,HealthWorker.SSN,HealthWorker.firstName,
       HealthWorker.lastName,HealthWorker.birthDate,HealthWorker.medicalCardNumber,
       HealthWorker.telephone,HealthWorker.address,HealthWorker.city,HealthWorker.province,HealthWorker.postalCode,
       HealthWorker.citizenShip,HealthWorker.email,HealthWorker.startDate,HealthWorker.endDate
from HealthWorker,Facility,Work
where HealthWorker.employeeId=Work.employeeId and Work.facilityName=Facility.facilityName and Work.facilityName='CLSC Montreal South';

#Q20:
SELECT HealthWorker.employeeID, HealthWorker.SSN, HealthWorker.firstName,HealthWorker.lastName, HealthWorker.birthDate,
       HealthWorker.telephone, HealthWorker.city, HealthWorker.email,Facility.facilityName
FROM HealthWorker, Facility, Work,Vaccination
WHERE  Facility.province  ='quebec' AND HealthWorker.employeeID = Work. employeeID AND Work.facilityName = Facility.facilityName
  and Vaccination.SSN=HealthWorker.SSN and Vaccination.doseNumber<=1;