-- phần 1: thiết kế csdl & chèn dữ liệu (25 điểm)
-- 1. thiết kế bảng (15 điểm)

-- tạo cơ sở dữ liệu
create database if not exists logistics_db;
use logistics_db;

-- bảng 1: shippers
create table shippers (
    ma_tai_xe int primary key,
    ho_ten varchar(100) not null,
    so_dien_thoai varchar(20) unique,
    loai_bang_lai varchar(10) not null,
    diem_danh_gia decimal(3,1) default 5.0 check (diem_danh_gia >= 0 and diem_danh_gia <= 5)
);

-- bảng 2: vehicle_details
create table vehicle_details (
    ma_phuong_tien int primary key,
    ma_tai_xe int,
    bien_so_xe varchar(20) unique,
    loai_xe varchar(50),
    trong_tai_toi_da decimal(10,2) check (trong_tai_toi_da > 0),
    foreign key (ma_tai_xe) references shippers(ma_tai_xe)
);

-- bảng 3: shipments
create table shipments (
    ma_van_don int primary key,
    ten_hang_hoa varchar(200),
    trong_luong_thuc_te decimal(10,2) check (trong_luong_thuc_te > 0),
    gia_tri_hang_hoa decimal(15,2),
    trang_thai varchar(50)
);

-- bảng 4: delivery_orders
create table delivery_orders (
    ma_phieu int primary key,
    ma_van_don int,
    ma_tai_xe_dam_nhan int,
    thoi_gian_dieu_phoi datetime default current_timestamp,
    phi_van_chuyen decimal(15,2),
    trang_thai_phieu varchar(50),
    foreign key (ma_van_don) references shipments(ma_van_don),
    foreign key (ma_tai_xe_dam_nhan) references shippers(ma_tai_xe)
);

-- bảng 5: delivery_log
create table delivery_log (
    ma_nhat_ky int primary key,
    ma_phieu_dieu_phoi int,
    vi_tri_hien_tai varchar(200),
    thoi_diem_ghi_nhan datetime,
    ghi_chu text,
    foreign key (ma_phieu_dieu_phoi) references delivery_orders(ma_phieu)
);

-- 2. dml (10 điểm): insert dữ liệu mẫu

-- insert shippers
insert into shippers values 
(1, 'Nguyen Van An', '0901234567', 'C', 4.8),
(2, 'Tran Thi Binh', '0912345678', 'A2', 5.0),
(3, 'Le Hoang Nam', '0983456789', 'FC', 4.2),
(4, 'Pham Minh Duc', '0354567890', 'B2', 4.9),
(5, 'Hoang Quoc Viet', '0775678901', 'C', 4.7);

-- insert vehicle_details
insert into vehicle_details values 
(101, 1, '29C-123.45', 'Tải', 3500),
(102, 2, '59A-888.88', 'Xe máy', 500),
(103, 3, '15R-999.99', 'Container', 32000),
(104, 4, '30F-111.22', 'Tải', 1500),
(105, 5, '43C-444.55', 'Tải', 5000);

-- insert shipments
insert into shipments values 
(5001, 'Smart TV Samsung 55 inch', 25.5, 15000000, 'In Transit'),
(5002, 'Laptop Dell XPS', 2.0, 35000000, 'Delivered'),
(5003, 'Máy nén khí công nghiệp', 450.0, 120000000, 'In Transit'),
(5004, 'Thùng trái cây nhập khẩu', 15.0, 2500000, 'Returned'),
(5005, 'Máy giặt LG Inverter', 70.0, 9500000, 'In Transit');

-- insert delivery_orders
insert into delivery_orders values 
(9001, 5001, 1, '2024-05-20 08:00:00', 2000000, 'Processing'),
(9002, 5002, 2, '2024-05-20 09:30:00', 3500000, 'Finished'),
(9003, 5003, 3, '2024-05-20 10:15:00', 2500000, 'Processing'),
(9004, 5004, 5, '2024-05-21 07:00:00', 1500000, 'Finished'),
(9005, 5005, 4, '2024-05-21 08:45:00', 2500000, 'Pending');

-- insert delivery_log
insert into delivery_log values 
(1, 9001, 'Kho tổng (Hà Nội)', '2021-05-15 08:15:00', 'Rời kho'),
(2, 9001, 'Trạm thu phí Phủ Lý', '2021-05-17 10:00:00', 'Đang giao'),
(3, 9002, 'Quận 1, TP.HCM', '2024-05-19 10:30:00', 'Đã đến điểm đích'),
(4, 9003, 'Cảng Hải Phòng', '2024-05-20 11:00:00', 'Rời kho'),
(5, 9004, 'Kho hoàn hàng (Đà Nẵng)', '2024-05-21 14:00:00', 'Đã nhập kho trả hàng');

-- 1. câu lệnh tăng phí vận chuyển thêm 10%
update delivery_orders d
join shipments s on d.ma_van_don = s.ma_van_don
set d.phi_van_chuyen = d.phi_van_chuyen * 1.1
where d.trang_thai_phieu = 'Finished' and s.trong_luong_thuc_te > 100;

-- 2. câu lệnh xóa các bản ghi trong nhật ký di chuyển trước ngày 17/05/2024
delete from delivery_log 
where thoi_diem_ghi_nhan < '2024-05-17 00:00:00';

-- phần 2: truy vấn dữ liệu cơ bản (15 điểm)

-- câu 1: liệt kê phương tiện
select bien_so_xe, loai_xe, trong_tai_toi_da 
from vehicle_details 
where trong_tai_toi_da > 5000 
   or (loai_xe = 'Container' and trong_tai_toi_da < 2000);

-- câu 2: lấy thông tin tài xế
select ho_ten, so_dien_thoai 
from shippers 
where diem_danh_gia between 4.5 and 5.0 
  and so_dien_thoai like '090%';

-- câu 3: phân trang (trang 2, mỗi trang 2 đơn) sắp xếp theo giá trị hàng hóa giảm dần
select s.ma_van_don, s.ten_hang_hoa, s.gia_tri_hang_hoa
from shipments s
order by s.gia_tri_hang_hoa desc
limit 2 offset 2;

-- phần 3: truy vấn dữ liệu nâng cao (20 điểm)

-- câu 1: hiển thị thông tin đơn hàng đầy đủ
select sh.ho_ten as ho_ten_tai_xe, s.ma_van_don, s.ten_hang_hoa, d.phi_van_chuyen, d.thoi_gian_dieu_phoi
from delivery_orders d
join shippers sh on d.ma_tai_xe_dam_nhan = sh.ma_tai_xe
join shipments s on d.ma_van_don = s.ma_van_don;

-- câu 2: tổng phí vận chuyển mỗi tài xế > 3tr
select d.ma_tai_xe_dam_nhan, sum(d.phi_van_chuyen) as tong_phi_van_chuyen
from delivery_orders d
group by d.ma_tai_xe_dam_nhan
having sum(d.phi_van_chuyen) > 3000000;

-- câu 3: tài xế có điểm đánh giá trung bình cao nhất
-- (lưu ý: cấu trúc bảng hiện tại điểm đánh giá nằm ở bảng shippers, không phải bảng đánh giá riêng, 
-- nên ta lấy trực tiếp từ bảng shippers)
select * from shippers 
order by diem_danh_gia desc 
limit 1;

-- phần 4: index và view (10 điểm)

-- câu 1: tạo composite index
create index idx_shipment_status_value on shipments(trang_thai, gia_tri_hang_hoa);

-- câu 2: tạo view vw_driver_performance
create view vw_driver_performance as
select sh.ho_ten, 
       count(d.ma_phieu) as tong_so_chuyen, 
       sum(d.phi_van_chuyen) as tong_doanh_thu
from shippers sh
join delivery_orders d on sh.ma_tai_xe = d.ma_tai_xe_dam_nhan
where d.trang_thai_phieu != 'Cancelled'
group by sh.ma_tai_xe, sh.ho_ten;

-- phần 5: trigger (10 điểm)

-- câu 1: trigger trg_after_delivery_finish
delimiter //
create trigger trg_after_delivery_finish
after update on delivery_orders
for each row
begin
    if new.trang_thai_phieu = 'Finished' and old.trang_thai_phieu != 'Finished' then
        insert into delivery_log(ma_nhat_ky, ma_phieu_dieu_phoi, vi_tri_hien_tai, thoi_diem_ghi_nhan, ghi_chu)
        values (
            (select ifnull(max(ma_nhat_ky), 0) + 1 from delivery_log as log_alias), -- tự tăng mã log đơn giản
            new.ma_phieu,
            'Tại điểm đích',
            now(),
            'Delivery Completed Successfully'
        );
    end if;
end //
delimiter ;

-- câu 2: trigger trg_update_driver_rating
delimiter //
create trigger trg_update_driver_rating
after insert on delivery_orders
for each row
begin
    if new.trang_thai_phieu = 'Finished' then
        update shippers
        set diem_danh_gia = least(diem_danh_gia + 0.1, 5.0)
        where ma_tai_xe = new.ma_tai_xe_dam_nhan;
    end if;
end //
delimiter ;

-- phần 6: stored procedure (20 điểm)

-- câu 1: procedure sp_check_payload_status
delimiter //
create procedure sp_check_payload_status(
    in p_ma_phuong_tien int,
    out p_message varchar(50)
)
begin
    declare v_trong_tai_toi_da decimal(10,2);
    declare v_trong_luong_thuc_te decimal(10,2);
    
    -- lấy trọng tải xe và trọng lượng hàng của đơn hàng mới nhất xe đó đang chở
    select v.trong_tai_toi_da, s.trong_luong_thuc_te
    into v_trong_tai_toi_da, v_trong_luong_thuc_te
    from vehicle_details v
    join delivery_orders d on v.ma_tai_xe = d.ma_tai_xe_dam_nhan
    join shipments s on d.ma_van_don = s.ma_van_don
    where v.ma_phuong_tien = p_ma_phuong_tien
    order by d.thoi_gian_dieu_phoi desc
    limit 1;
    
    if v_trong_luong_thuc_te > v_trong_tai_toi_da then
        set p_message = 'Quá tải';
    elseif v_trong_luong_thuc_te = v_trong_tai_toi_da then
        set p_message = 'Đầy tải';
    else
        set p_message = 'An toàn';
    end if;
end //
delimiter ;

-- câu 2: procedure sp_reassign_driver
delimiter //
create procedure sp_reassign_driver(
    in p_ma_phieu int,
    in p_ma_tai_xe_moi int
)
begin
    declare exit handler for sqlexception
    begin
        rollback;
    end;

    start transaction;
        -- b2: cập nhật mã tài xế mới
        update delivery_orders
        set ma_tai_xe_dam_nhan = p_ma_tai_xe_moi
        where ma_phieu = p_ma_phieu;
        
        -- b3: ghi nhật ký
        insert into delivery_log(ma_nhat_ky, ma_phieu_dieu_phoi, vi_tri_hien_tai, thoi_diem_ghi_nhan, ghi_chu)
        values (
            (select ifnull(max(ma_nhat_ky), 0) + 1 from delivery_log as log_alias),
            p_ma_phieu,
            'Trạm điều phối',
            now(),
            'Driver Reassigned'
        );
        
    commit;
end //
delimiter ;
