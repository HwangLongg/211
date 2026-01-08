-- khởi tạo cơ sở dữ liệu
create database studio_management;
use studio_management;

-- =============================================================
-- phần 1: tạo cấu trúc bảng và chèn dữ liệu
-- =============================================================

-- 1. tạo bảng creator
create table creator (
    creator_id varchar(5) primary key,
    creator_name varchar(100) not null,
    creator_email varchar(100) not null unique,
    creator_phone varchar(15) not null unique,
    creator_platform varchar(50) not null
);

-- 2. tạo bảng studio
create table studio (
    studio_id varchar(5) primary key,
    studio_name varchar(100) not null,
    studio_location varchar(100) not null,
    hourly_price decimal(10,2) not null,
    studio_status varchar(20) not null
);

-- 3. tạo bảng livesession (phiên livestream)
create table livesession (
    session_id int primary key auto_increment,
    creator_id varchar(5) not null,
    studio_id varchar(5) not null,
    session_date date not null,
    duration_hours int not null,
    foreign key (creator_id) references creator(creator_id),
    foreign key (studio_id) references studio(studio_id)
);

-- 4. tạo bảng payment (thanh toán)
create table payment (
    payment_id int primary key auto_increment,
    session_id int not null,
    payment_method varchar(50) not null,
    payment_amount decimal(10,2) not null,
    payment_date date not null,
    foreign key (session_id) references livesession(session_id)
);

-- 5. chèn dữ liệu mẫu
insert into creator (creator_id, creator_name, creator_email, creator_phone, creator_platform) values
('cr01', 'nguyen van a', 'a@live.com', '0901111111', 'tiktok'),
('cr02', 'tran thi b', 'b@live.com', '0902222222', 'youtube'),
('cr03', 'le minh c', 'c@live.com', '0903333333', 'facebook'),
('cr04', 'pham thi d', 'd@live.com', '0904444444', 'tiktok'),
('cr05', 'vu hoang e', 'e@live.com', '0905555555', 'shopee live');

insert into studio (studio_id, studio_name, studio_location, hourly_price, studio_status) values
('st01', 'studio a', 'ha noi', 20.00, 'available'),
('st02', 'studio b', 'hcm', 25.00, 'available'),
('st03', 'studio c', 'danang', 30.00, 'booked'),
('st04', 'studio d', 'ha noi', 22.00, 'available'),
('st05', 'studio e', 'can tho', 18.00, 'maintenance');

insert into livesession (creator_id, studio_id, session_date, duration_hours) values
('cr01', 'st01', '2025-05-01', 3),
('cr02', 'st02', '2025-05-02', 4),
('cr03', 'st03', '2025-05-03', 2),
('cr01', 'st04', '2025-05-04', 5),
('cr05', 'st02', '2025-05-05', 1);

insert into payment (session_id, payment_method, payment_amount, payment_date) values
(1, 'cash', 60.00, '2025-05-01'),
(2, 'credit card', 100.00, '2025-05-02'),
(3, 'bank transfer', 60.00, '2025-05-03'),
(4, 'credit card', 110.00, '2025-05-04'),
(5, 'cash', 25.00, '2025-05-05');

-- 6. cập nhật & xóa dữ liệu
-- cập nhật nền tảng cho creator cr03
update creator set creator_platform = 'youtube' where creator_id = 'cr03';

-- cập nhật studio st05 hoạt động trở lại và giảm giá 10%
update studio 
set studio_status = 'available', 
    hourly_price = hourly_price * 0.9 
where studio_id = 'st05';

-- xóa các thanh toán tiền mặt (cash) trước ngày 2025-05-03
delete from payment 
where payment_method = 'cash' and payment_date < '2025-05-03';


-- =============================================================
-- phần 2: truy vấn dữ liệu cơ bản
-- =============================================================

-- 1. liệt kê studio có trạng thái available và giá > 20
select * from studio where studio_status = 'available' and hourly_price > 20;

-- 2. lấy thông tin creator có nền tảng tiktok
select creator_name, creator_phone from creator where creator_platform = 'tiktok';

-- 3. danh sách studio sắp xếp theo giá thuê giảm dần
select studio_id, studio_name, hourly_price from studio order by hourly_price desc;

-- 4. lấy 3 payment đầu tiên có phương thức credit card
select * from payment where payment_method = 'credit card' limit 3;

-- 5. lấy danh sách creator, bỏ qua 2 người đầu và lấy 2 người tiếp theo
select creator_id, creator_name from creator limit 2 offset 2;


-- =============================================================
-- phần 3: truy vấn dữ liệu nâng cao
-- =============================================================

-- 1. danh sách livestream chi tiết gồm: id, tên creator, tên studio, số giờ, tiền thanh toán
select l.session_id, c.creator_name, s.studio_name, l.duration_hours, p.payment_amount
from livesession l
join creator c on l.creator_id = c.creator_id
join studio s on l.studio_id = s.studio_id
join payment p on l.session_id = p.session_id;

-- 2. liệt kê tất cả studio và số lần được sử dụng (kể cả studio chưa thuê)
select s.studio_id, s.studio_name, count(l.session_id) as usage_count
from studio s
left join livesession l on s.studio_id = l.studio_id
group by s.studio_id, s.studio_name;

-- 3. tính tổng doanh thu theo từng phương thức thanh toán
select payment_method, sum(payment_amount) as total_revenue
from payment
group by payment_method;

-- 4. thống kê số session của mỗi creator (chỉ lấy người có từ 2 session trở lên)
select c.creator_name, count(l.session_id) as session_count
from creator c
join livesession l on c.creator_id = l.creator_id
group by c.creator_id, c.creator_name
having count(l.session_id) >= 2;

-- 5. lấy studio có giá thuê cao hơn mức trung bình của tất cả studio
select * from studio 
where hourly_price > (select avg(hourly_price) from studio);

-- 6. hiển thị creator đã từng livestream tại studio b
select distinct c.creator_name, c.creator_email
from creator c
join livesession l on c.creator_id = l.creator_id
join studio s on l.studio_id = s.studio_id
where s.studio_name = 'studio b';

-- 7. báo cáo tổng hợp thông tin phiên live và thanh toán
select l.session_id, c.creator_name, s.studio_name, p.payment_method, p.payment_amount
from livesession l
join creator c on l.creator_id = c.creator_id
join studio s on l.studio_id = s.studio_id
join payment p on l.session_id = p.session_id;
