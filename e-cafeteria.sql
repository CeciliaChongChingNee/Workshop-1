-- phpMyAdmin SQL Dump
-- version 5.0.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jan 25, 2021 at 02:55 PM
-- Server version: 10.4.11-MariaDB
-- PHP Version: 7.4.3

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `e-cafeteria`
--
CREATE DATABASE IF NOT EXISTS `e-cafeteria` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;
USE `e-cafeteria`;

-- --------------------------------------------------------

--
-- Table structure for table `budget`
--

CREATE TABLE `budget` (
  `Budget_ID` varchar(10) NOT NULL,
  `Customer_ID` int(5) NOT NULL,
  `Budget_Type_ID` varchar(10) NOT NULL,
  `Budget_StartDate` date DEFAULT NULL,
  `Budget_Status` char(10) NOT NULL DEFAULT 'Off',
  `Budget_TotalAmount` double NOT NULL,
  `Budget_Repeated` char(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `budget`
--

INSERT INTO `budget` (`Budget_ID`, `Customer_ID`, `Budget_Type_ID`, `Budget_StartDate`, `Budget_Status`, `Budget_TotalAmount`, `Budget_Repeated`) VALUES
('B001', 7, 'G002', '2021-01-17', 'ACTIVE', 70, 'N'),
('B002', 11, 'G002', '2021-01-17', 'ACTIVE', 100, 'N'),
('B003', 6, 'G001', '2021-01-17', 'ACTIVE', 30, 'Y'),
('B004', 6, 'G002', '2021-01-17', 'STANDBY', 100, 'Y'),
('B005', 2, 'G001', '2021-01-25', 'STANDBY', 50, 'Y'),
('B006', 2, 'G002', '2021-01-25', 'ACTIVE', 50, 'Y');

-- --------------------------------------------------------

--
-- Table structure for table `budget type`
--

CREATE TABLE `budget type` (
  `Budget_Type_ID` varchar(10) NOT NULL,
  `Budget_Label` char(10) NOT NULL,
  `Budget_Duration` int(2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `budget type`
--

INSERT INTO `budget type` (`Budget_Type_ID`, `Budget_Label`, `Budget_Duration`) VALUES
('G001', 'Daily', 1),
('G002', 'Weekly', 7);

-- --------------------------------------------------------

--
-- Table structure for table `meal type`
--

CREATE TABLE `meal type` (
  `Meal_Type_ID` varchar(10) NOT NULL,
  `Type_Name` char(10) NOT NULL,
  `Time_Start` time NOT NULL,
  `Time_End` time NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `meal type`
--

INSERT INTO `meal type` (`Meal_Type_ID`, `Type_Name`, `Time_Start`, `Time_End`) VALUES
('T001', 'Breakfast', '07:00:00', '11:30:00'),
('T002', 'Brunch', '10:00:00', '14:00:00'),
('T003', 'Lunch', '12:30:00', '17:00:00'),
('T004', 'Dinner', '18:00:00', '22:00:00'),
('T005', 'Supper', '22:30:00', '23:59:00'),
('T006', 'All Day', '00:00:00', '23:59:00');

-- --------------------------------------------------------

--
-- Table structure for table `menu`
--

CREATE TABLE `menu` (
  `Menu_ID` varchar(10) NOT NULL,
  `Vendor_ID` int(5) NOT NULL,
  `Meal_Type_ID` varchar(10) NOT NULL,
  `Menu_Name` varchar(50) NOT NULL,
  `Menu_Description` varchar(100) NOT NULL,
  `Menu_Quantity` int(3) NOT NULL,
  `Menu_Price` double NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `menu`
--

INSERT INTO `menu` (`Menu_ID`, `Vendor_ID`, `Meal_Type_ID`, `Menu_Name`, `Menu_Description`, `Menu_Quantity`, `Menu_Price`) VALUES
('M001', 3, 'T001', 'American Breakfast', 'scrambled eggs, sausages and potatoes', 15, 3.5),
('M002', 10, 'T001', 'Nasi Lemak', 'fragrant rice,fried egg and cucumber', 14, 1.5),
('M003', 9, 'T001', 'Nasi Lemak with Fried Chicken', 'fragrant rice, fried chicken and fried egg', 25, 5),
('M004', 5, 'T001', 'Roti Canai', 'flatbread with curry sauce', 20, 1),
('M005', 9, 'T003', 'Herbal Chicken with Rice', 'herbal chicken soup and rice', 20, 6.5),
('M006', 3, 'T003', 'Grilled Chicken Chop', 'chicken chop, rice, french fries and salad', 1, 5),
('M007', 5, 'T003', 'Mee Siam with Curry Chicken', 'mee siam, curry chicken and fried egg', 5, 3),
('M008', 10, 'T003', 'Fried Rice with Fried Chicken', 'fried rice, fried chicken and fried egg', 15, 4.5),
('M009', 3, 'T004', 'Chicken Carbonara Spaghetti', 'carbonara spaghetti and grilled chicken chop', 9, 5),
('M010', 5, 'T004', 'Lamb Soup with Fried Rice', 'lamb soup and fried rice', 5, 3.5),
('M011', 9, 'T004', 'Gong Bao Chicken with Rice', 'Gong Bao chicken, rice and fried egg', 30, 4.5),
('M012', 10, 'T004', 'Tomyam Seafood Maggie Soup', 'seafood, chicken, vegetable and maggie tomyam', 18, 4),
('M013', 3, 'T006', 'Lemon Tea (Hot)', 'hot tea with lemon', 25, 1.5),
('M014', 3, 'T006', 'Lemon Tea (Cold)', 'tea with lemon and ice', 21, 2),
('M015', 5, 'T006', 'Tea Tarik (Hot)', 'hot milk tea', 19, 1),
('M016', 5, 'T006', 'Tea Tarik (Cold)', 'milk tea with ice', 18, 1.5),
('M017', 10, 'T006', 'Sirap Bandung (Cold)', 'rose syrup, milk and ice', 10, 2.5),
('M018', 9, 'T006', 'Herbal Tea (Hot)', 'tea with grass jelly', 19, 1.2);

-- --------------------------------------------------------

--
-- Table structure for table `order`
--

CREATE TABLE `order` (
  `Order_ID` varchar(10) NOT NULL,
  `Customer_ID` int(5) NOT NULL,
  `Vendor_ID` int(5) NOT NULL,
  `Order_Type` varchar(10) NOT NULL,
  `Order_Address` varchar(50) NOT NULL DEFAULT 'Cafe',
  `Order_Date` date NOT NULL,
  `Order_ExpectedTime` time NOT NULL,
  `Order_TotalAmount` double NOT NULL,
  `Order_Status` char(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `order`
--

INSERT INTO `order` (`Order_ID`, `Customer_ID`, `Vendor_ID`, `Order_Type`, `Order_Address`, `Order_Date`, `Order_ExpectedTime`, `Order_TotalAmount`, `Order_Status`) VALUES
('D001', 7, 9, 'Order', 'CAFE', '2021-01-14', '20:14:50', 5.7, 'Accept'),
('D002', 4, 5, 'Booking', 'Lekir Satria L4-B8-A', '2021-01-14', '08:00:00', 1, 'Processing'),
('D003', 4, 10, 'Booking', 'Lekir Satria L4-B8-A', '2021-01-14', '08:00:00', 1.5, 'Processing'),
('D004', 11, 3, 'Booking', 'Lekir Satria L10-B11-C', '2021-01-17', '13:00:00', 7, 'Processing'),
('D005', 11, 5, 'Order', 'CAFE', '2021-01-17', '19:52:10', 1.5, 'Processing'),
('D006', 11, 10, 'Order', 'CAFE', '2021-01-17', '19:52:10', 4, 'Accept'),
('D007', 11, 3, 'Booking', 'Lekir Satria L11-B10-C', '2021-01-17', '13:00:00', 7, 'Processing'),
('D008', 11, 9, 'Booking', 'Lekir Satria L11-B10-C', '2021-01-17', '13:00:00', 7.7, 'Processing'),
('D009', 11, 3, 'Booking', 'Lekir Satria L11-B10-C', '2021-01-17', '13:00:00', 7, 'Processing'),
('D010', 11, 3, 'Booking', 'Lekir Satria L11-B10-C', '2021-01-17', '13:00:00', 7, 'Processing'),
('D011', 11, 5, 'Order', 'CAFE', '2021-01-17', '20:14:12', 1.5, 'Processing'),
('D012', 11, 10, 'Order', 'CAFE', '2021-01-17', '20:14:12', 4, 'Done'),
('D013', 4, 10, 'Order', 'CAFE', '2021-01-17', '20:35:01', 4, 'Processing'),
('D014', 4, 10, 'Order', 'CAFE', '2021-01-17', '20:37:23', 4, 'Processing'),
('D015', 4, 10, 'Order', 'CAFE', '2021-01-17', '20:39:19', 4, 'Processing'),
('D016', 11, 10, 'Order', 'CAFE', '2021-01-17', '20:53:32', 4, 'Processing'),
('D017', 11, 10, 'Order', 'CAFE', '2021-01-17', '20:56:51', 4, 'Processing'),
('D018', 2, 3, 'Order', 'CAFE', '2021-01-25', '20:25:34', 5, 'Processing');

-- --------------------------------------------------------

--
-- Table structure for table `order detail`
--

CREATE TABLE `order detail` (
  `Order_Detail_ID` varchar(10) NOT NULL,
  `Order_ID` varchar(10) NOT NULL,
  `Customer_ID` int(5) NOT NULL,
  `Menu_ID` varchar(10) NOT NULL,
  `Item_Quantity` int(3) NOT NULL,
  `Total_Item_Price` double NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `order detail`
--

INSERT INTO `order detail` (`Order_Detail_ID`, `Order_ID`, `Customer_ID`, `Menu_ID`, `Item_Quantity`, `Total_Item_Price`) VALUES
('L001', 'D001', 7, 'M018', 1, 1.2),
('L002', 'D001', 7, 'M011', 1, 4.5),
('L003', 'D002', 4, 'M015', 1, 1),
('L004', 'D003', 4, 'M002', 1, 1.5),
('L005', 'D004', 11, 'M014', 1, 2),
('L006', 'D004', 11, 'M006', 1, 5),
('L007', 'D005', 11, 'M016', 1, 1.5),
('L008', 'D006', 11, 'M012', 1, 4),
('L009', 'D007', 11, 'M014', 1, 2),
('L010', 'D007', 11, 'M006', 1, 5),
('L011', 'D008', 11, 'M005', 1, 6.5),
('L012', 'D008', 11, 'M018', 1, 1.2),
('L013', 'D009', 11, 'M014', 1, 2),
('L014', 'D009', 11, 'M006', 1, 5),
('L015', 'D010', 11, 'M014', 1, 2),
('L016', 'D010', 11, 'M006', 1, 5),
('L017', 'D011', 11, 'M016', 1, 1.5),
('L018', 'D012', 11, 'M012', 1, 4),
('L019', 'D013', 4, 'M012', 1, 4),
('L020', 'D014', 4, 'M012', 1, 4),
('L021', 'D015', 4, 'M012', 1, 4),
('L022', 'D016', 11, 'M012', 1, 4),
('L023', 'D017', 11, 'M012', 1, 4),
('L024', 'D018', 2, 'M009', 1, 5);

-- --------------------------------------------------------

--
-- Table structure for table `payment`
--

CREATE TABLE `payment` (
  `Order_ID` varchar(10) NOT NULL,
  `Customer_ID` int(5) NOT NULL,
  `Payment_TotalAmount` double NOT NULL,
  `Payment_Date` date NOT NULL,
  `Payment_Time` time NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `payment`
--

INSERT INTO `payment` (`Order_ID`, `Customer_ID`, `Payment_TotalAmount`, `Payment_Date`, `Payment_Time`) VALUES
('D001', 7, 5.7, '2021-01-14', '20:18:35'),
('D002', 4, 1, '2021-01-14', '20:42:52'),
('D003', 4, 1.5, '2021-01-17', '20:36:45'),
('D004', 11, 7, '2021-01-17', '19:54:35'),
('D005', 11, 1.5, '2021-01-17', '19:53:22'),
('D006', 11, 4, '2021-01-17', '19:53:42'),
('D007', 11, 7, '2021-01-17', '20:02:03'),
('D008', 11, 7.7, '2021-01-17', '20:02:06'),
('D009', 11, 7, '2021-01-17', '20:11:00'),
('D010', 11, 7, '2021-01-17', '20:16:26'),
('D011', 11, 1.5, '2021-01-17', '20:15:13'),
('D012', 11, 4, '2021-01-17', '20:15:38'),
('D013', 4, 4, '2021-01-17', '20:36:56'),
('D014', 4, 4, '2021-01-17', '20:38:48');

-- --------------------------------------------------------

--
-- Table structure for table `user`
--

CREATE TABLE `user` (
  `User_ID` int(5) NOT NULL,
  `User_Name` varchar(30) NOT NULL,
  `User_Type` varchar(10) NOT NULL,
  `User_IdentityCard` varchar(15) NOT NULL,
  `User_Password` varchar(10) NOT NULL,
  `User_Gender` char(1) NOT NULL,
  `User_PhoneNumber` varchar(12) NOT NULL,
  `User_Balance` double NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `user`
--

INSERT INTO `user` (`User_ID`, `User_Name`, `User_Type`, `User_IdentityCard`, `User_Password`, `User_Gender`, `User_PhoneNumber`, `User_Balance`) VALUES
(1, 'Cecilia Chong Ching Nee', 'Admin', '990909-10-9992', 'yes999', 'P', '018-3746877', 0),
(2, 'Jackie Sow Chen Wei', 'Customer', '960612-01-6671', 'wei0612', 'L', '012-7981120', 150),
(3, 'Ahmad Alif Bin Abdul Hadi', 'Vendor', '810128-04-7763', 'alif0128', 'L', '012-7344395', 28),
(4, 'Siti Nur Aida Binti Halim', 'Customer', '901201-08-6546', 'aida123', 'P', '011-3221462', 89.5),
(5, 'Asitha A/P Gadanesam', 'Vendor', '740214-03-5782', 'asitha74', 'P', '014-7116782', 4),
(6, 'Ravin A/L Selvam', 'Customer', '960918-01-3675', 'ravin0918', 'L', '012-7685922', 120),
(7, 'Nurul Ain Binti Azhar', 'Customer', '000312-11-5178', 'ain0312', 'P', '018-7765331', 244.3),
(8, 'Ahmad Haris Bin Abdul Rizal', 'Vendor', '791231-05-1127', 'haris79', 'L', '013-2116678', 0),
(9, 'Stella Fong Ying Yu', 'Vendor', '880204-02-4484', 'stella888', 'P', '015-5466811', 13.4),
(10, 'Abdul Fikri Bin Abdullah', 'Vendor', '770529-06-3153', 'fikri123', 'L', '016-3289571', 17.5),
(11, 'Selvi A/P Kumar', 'Customer', '990702-08-1198', 'selvi99', 'P', '013-7814465', 30.5);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `budget`
--
ALTER TABLE `budget`
  ADD PRIMARY KEY (`Budget_ID`),
  ADD KEY `Customer_ID` (`Customer_ID`),
  ADD KEY `Budget_Type_ID` (`Budget_Type_ID`);

--
-- Indexes for table `budget type`
--
ALTER TABLE `budget type`
  ADD PRIMARY KEY (`Budget_Type_ID`);

--
-- Indexes for table `meal type`
--
ALTER TABLE `meal type`
  ADD PRIMARY KEY (`Meal_Type_ID`);

--
-- Indexes for table `menu`
--
ALTER TABLE `menu`
  ADD PRIMARY KEY (`Menu_ID`),
  ADD KEY `Meal_Type_ID` (`Meal_Type_ID`),
  ADD KEY `User_ID` (`Vendor_ID`) USING BTREE;

--
-- Indexes for table `order`
--
ALTER TABLE `order`
  ADD PRIMARY KEY (`Order_ID`),
  ADD KEY `Customer_ID` (`Customer_ID`),
  ADD KEY `Vendor_ID` (`Vendor_ID`);

--
-- Indexes for table `order detail`
--
ALTER TABLE `order detail`
  ADD PRIMARY KEY (`Order_Detail_ID`),
  ADD KEY `Order_ID` (`Order_ID`),
  ADD KEY `Customer_ID` (`Customer_ID`),
  ADD KEY `Menu_ID` (`Menu_ID`);

--
-- Indexes for table `payment`
--
ALTER TABLE `payment`
  ADD PRIMARY KEY (`Order_ID`),
  ADD KEY `Customer_ID` (`Customer_ID`);

--
-- Indexes for table `user`
--
ALTER TABLE `user`
  ADD PRIMARY KEY (`User_ID`),
  ADD UNIQUE KEY `User_IdentityCard` (`User_IdentityCard`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `user`
--
ALTER TABLE `user`
  MODIFY `User_ID` int(5) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=12;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `budget`
--
ALTER TABLE `budget`
  ADD CONSTRAINT `budget_ibfk_1` FOREIGN KEY (`Customer_ID`) REFERENCES `user` (`User_ID`),
  ADD CONSTRAINT `budget_ibfk_2` FOREIGN KEY (`Budget_Type_ID`) REFERENCES `budget type` (`Budget_Type_ID`);

--
-- Constraints for table `menu`
--
ALTER TABLE `menu`
  ADD CONSTRAINT `menu_ibfk_1` FOREIGN KEY (`Vendor_ID`) REFERENCES `user` (`User_ID`),
  ADD CONSTRAINT `menu_ibfk_2` FOREIGN KEY (`Meal_Type_ID`) REFERENCES `meal type` (`Meal_Type_ID`);

--
-- Constraints for table `order`
--
ALTER TABLE `order`
  ADD CONSTRAINT `order_ibfk_1` FOREIGN KEY (`Customer_ID`) REFERENCES `user` (`User_ID`),
  ADD CONSTRAINT `order_ibfk_2` FOREIGN KEY (`Vendor_ID`) REFERENCES `user` (`User_ID`);

--
-- Constraints for table `order detail`
--
ALTER TABLE `order detail`
  ADD CONSTRAINT `order detail_ibfk_1` FOREIGN KEY (`Order_ID`) REFERENCES `order` (`Order_ID`),
  ADD CONSTRAINT `order detail_ibfk_2` FOREIGN KEY (`Customer_ID`) REFERENCES `user` (`User_ID`),
  ADD CONSTRAINT `order detail_ibfk_3` FOREIGN KEY (`Menu_ID`) REFERENCES `menu` (`Menu_ID`);

--
-- Constraints for table `payment`
--
ALTER TABLE `payment`
  ADD CONSTRAINT `payment_ibfk_1` FOREIGN KEY (`Customer_ID`) REFERENCES `user` (`User_ID`),
  ADD CONSTRAINT `payment_ibfk_2` FOREIGN KEY (`Order_ID`) REFERENCES `order` (`Order_ID`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
