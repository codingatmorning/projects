


--CREATE VIEW view_name AS
--SELECT column1, column2, ...
--FROM table_name
--WHERE condition;


select *
from ledger


select distinct person 
from ledger
where action='PAID';



select *
from ledger

where item='THRESHING';

--check what items have been recieved, and what items are used.

select *
from ledger

where item='BOOT BETWEEN HORSES';


select *
from ledger
where action='RECEIVED';

select *
from ledger

where item='TELEPHONE CALL'

--check all the recieved items to see what their porpuses is


select *
from ledger

where PERSON='ADAH TALBOT';

--is helping me identify what the porpuse of recieved is and now i know that recieved is items that farm has acquired from their employees doing work.
select * from ledger
where item in (
select item
from ledger
where action='RECEIVED')

--These are all the items
select distinct item from ledger
where  item in(
select  item from ledger
where action='BOUGHT' or action='RECIEVED' or action='SOLD')


select * from ledger
where action='BOUGHT' or action='RECIEVED' or action='SOLD'

--used to see info about whole inventory
select * from ledger
where action='BOUGHT' or action='RECIEVED'



--This finds the rate cost of all the items. i found the telephone item kinda odd so i did a where statment to see the info about it turns out they charge a flat rate per call.
select avg(rate) from ledger
where  item in(
select  item from ledger
where action='BOUGHT' or action='RECIEVED')
group by item
order by item

--Amount of each item
select sum(quantity) from ledger
where  item in(
select  item from ledger
where action='BOUGHT' or action='RECIEVED')
group by item
order by item


--I found that the quantity type for the same item can be different.
select item,quantitytype from(
select distinct item, quantitytype from ledger
where  item in(
select  item from ledger
where action='BOUGHT' or action='RECIEVED' or action='SOLD') 
group by (item, quantitytype)
order by item, quantitytype)




--This query returns the name of items that use more than one quantity to describe the amount of an item
select item,quanttypes
from(
select item, count(item) as quanttypes
from 
(select distinct item, quantitytype 
from ledger
where  item in ( 
select  item 
from ledger
where action='BOUGHT' or action='RECEIVED' or action='SOLD')
group by (item, quantitytype) 
)
group by item
order by count(item) desc
)
where quanttypes>1
--Also because of this the amount isnt accurate cause the unit bushel is used and a bushel=60 pounds. so the quantity should be 60 lbs, and the amount instead would be around 100 dollars

--for future devolpment we can make a check to see if the quantity type does not match with the quantity type of the same item, then you cant enter it. this will help to streamline the operations
--so to fix this now well just update a few columns so the quantity types match up for that item. So when orderin hominy you dont make one order in pounds, and the other in bushels.
-- this will help so that way you will know what unit of measure your total inventory of a particular item is in. so one day you order 6 pounds, and the other day you order 2 bushels. 
--How are you gonna calculate the total amount from that.this also would in turn put less stress on the developers or analysts, so they can do thier job quicker and you dont have to pay them as much.

select distinct * from ledger where item in (
select item from(
select item,quanttypes
from(
select item, count(item) as quanttypes
from 
(select distinct item, quantitytype 
from ledger 
where  item in ( 
select  item 
from ledger
where action='BOUGHT' or action='RECIEVED' or action='SOLD')
group by (item, quantitytype) 
)
group by item
order by count(item) desc
)
where quanttypes>1)
)
--heres the update statments to help  normalize the database
update ledger
set quantitytype='LB', quantity=60, rate=rate/60
where item='HOMINY' and quantitytype='BUSHEL'

update ledger
set quantitytype='LB'
where item='HOMINY' and quantitytype='TERM'

update ledger
set quantitytype='LB'
where item='CALF MEAL' and quantitytype='EACH'

update ledger
set quantitytype='EACH'
where item='COLT' and quantitytype='COLT'




--so after analyzing the database a little futher i noticed that rates can be different
--so normalizing the database will prove dificult so instead ima just try to summarize the data as good as possible.

--so the rate varies from product, to product.

select item, sum(quantity),quantitytype,rate,amount
from ledger 
where  item in ( 
select  item 
from ledger
where action='BOUGHT')
group by item, quantity,quantitytype,rate,amount
order by item

--total value for each type of item bought throughout the year

--our previous update staments made this possible
--we gotta compare items sold to items bought to see if the store is making money i believe.
create view item_br as
select item,sum(quantity) as totalquan, quantitytype, sum(amount) as totalvalue
from ledger
where action='BOUGHT' or action='RECEIVED' 
group by item, quantitytype
order by item ;

create view item_s as
select item,sum(quantity) as totalquan, quantitytype, sum(amount) as totalvalue
from ledger
where action='SOLD'
group by item, quantitytype
order by item ;


drop view item_br;
drop view item_s;
commit;
--we notice the list of items sold is substantialy lower, than the amount of items bought.

--the rate is kinda uncessary, but we can analyze it later
--so these are all the items they sell directly


select row_number()over(order by 0)hi,row_number()over(order by 0)bye, sum(item_s.totalvalue) as grandtotal_s, sum(item_br.totalvalue) as grandtotal_br,sum(item_s.totalvalue)  - sum(item_br.totalvalue) as Profit
from item_s
inner join item_br
on item_s.item=item_br.item
group by
union all
select item_s.item,item_s.totalvalue as totalvalue_s, item_br.totalvalue as totalvalue_br,0,0,0
from item_s
inner join item_br
on item_s.item=item_br.item


create view v_ij_totals as select temp.* from(
select  item_tbl.*, sum_tbl.* from 
(
select '(null)'as "-",sum(item_s.totalvalue) as grandtotal_s,
sum(item_br.totalvalue) as grandtotal_br,
sum(item_s.totalvalue)  - sum(item_br.totalvalue) as Profit
from item_s
inner join item_br
on item_s.item=item_br.item) sum_tbl
full join 
(select item_s.item, 
item_s.totalvalue as totalvalue_s, 
item_br.totalvalue as totalvalue_br
from item_s
inner join item_br
on item_s.item=item_br.item) item_tbl
on item_tbl.item=sum_tbl."-")temp

drop table v_ij_totals
commit









select s.item,s.totalvalue-b.totalvalue as Profit
from item_s s
inner join item_br b
on s.item=b.item

select distinct item from ledger
order by item

select distinct item from ledger
where action='PAID'
order by item


--i needed to make sure that my value were correct for the sold and bought/recieved category in terms of quantity and amount so  i went in and manually changed the quantity
select  * 
from ledger
where action='SOLD'

commit
--explain plan for
--SELECT * FROM TABLE(DBMS_XPLAN.DISPLAY);


--where not = to select left side only
create view temppaid as


select * from ledger where action='BOUGHT'
 
 
select * from ledger
where  person in (select bp.* from
(select distinct person from ledger
where action='BOUGHT')bp
right join
(select distinct person from ledger 
where action='PAID')pp
on bp.person=pp.person) or action=bought
order by person 



--so if employee is in the bought section for everycase that means they bought it for the store like what is schooling
--then heifer and hefer


select * from ledger
where item='COLT'

update ledger
set quantitytype='EACH'
where quantitytype='COLT' and item='COLT'

select item_s.item, item_s.totalvalue as sold, item_br.totalvalue as bought, item_s.totalvalue-item_br.totalvalue as profit
from item_s
inner join item_br
on item_s.item=item_br.item

select tbl.item, tbl.totalquan as quansold, item_br.totalquan as quanbought
from
(select item,totalquan from item_s
where item in(
select item_s.item
from item_s
inner join item_br
on item_s.item=item_br.item))tbl
left join item_br
on tbl.item=item_br.item
