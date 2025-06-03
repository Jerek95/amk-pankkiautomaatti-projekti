-- MySQL dump 10.13  Distrib 8.0.41, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: bank_database
-- ------------------------------------------------------
-- Server version	8.2.0

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `asiakas`
--

DROP TABLE IF EXISTS `asiakas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `asiakas` (
  `tunnus` varchar(45) NOT NULL,
  `etunimi` varchar(45) DEFAULT NULL,
  `sukunimi` varchar(45) DEFAULT NULL,
  `osoite` varchar(45) DEFAULT NULL,
  `puhelinnumero` int DEFAULT NULL,
  PRIMARY KEY (`tunnus`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `asiakas`
--

LOCK TABLES `asiakas` WRITE;
/*!40000 ALTER TABLE `asiakas` DISABLE KEYS */;
INSERT INTO `asiakas` VALUES ('111','Aku','Ankka','Ankkalinna',40636),('222','Mikki','Hiiri','Ankkalinna',40111222),('333','Hessu','Hopo','Hanhivaara',40222333);
/*!40000 ALTER TABLE `asiakas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `kortti`
--

DROP TABLE IF EXISTS `kortti`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `kortti` (
  `kortinnumero` varchar(45) NOT NULL,
  `pinkoodi` varchar(255) DEFAULT NULL,
  `omistaja` varchar(45) DEFAULT NULL,
  `tilinumero` varchar(45) DEFAULT NULL,
  `kortinlukija` varchar(30) DEFAULT NULL,
  PRIMARY KEY (`kortinnumero`),
  KEY `kortti_asiakas_idx` (`omistaja`),
  KEY `kortti_tili_idx` (`tilinumero`),
  CONSTRAINT `kortti_asiakas` FOREIGN KEY (`omistaja`) REFERENCES `asiakas` (`tunnus`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `kortti_tili` FOREIGN KEY (`tilinumero`) REFERENCES `tili` (`tilinumero`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `kortti`
--

LOCK TABLES `kortti` WRITE;
/*!40000 ALTER TABLE `kortti` DISABLE KEYS */;
INSERT INTO `kortti` VALUES ('0500CB33C7','$2b$10$6awpLIdqr2x39n0wQQoSz.DKkmW1X6Uhb.AQ0V5XGqGd7eoGf5qKy','333','FI300333','lukittu'),('06000620D0','$2b$10$425t4REdTQzYZxGPLXvedu58EVgAXN569GTB37pMxpTRrcE5PMgQ6','222','FI300222','true'),('060006235F','$2b$10$DrXkBd993YVXggjZ1zuyqOPoOuEH.6J6K/yXJWnHT5dDCGophhVzO','111','FI300502','true');
/*!40000 ALTER TABLE `kortti` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tili`
--

DROP TABLE IF EXISTS `tili`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tili` (
  `tilinumero` varchar(45) NOT NULL,
  `saldo` decimal(10,2) DEFAULT NULL,
  `omistaja` varchar(45) DEFAULT NULL,
  `luottoraja` decimal(10,2) DEFAULT NULL,
  PRIMARY KEY (`tilinumero`),
  KEY `tili_asiakas_idx` (`omistaja`),
  CONSTRAINT `tili_asiakas` FOREIGN KEY (`omistaja`) REFERENCES `asiakas` (`tunnus`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tili`
--

LOCK TABLES `tili` WRITE;
/*!40000 ALTER TABLE `tili` DISABLE KEYS */;
INSERT INTO `tili` VALUES ('FI300222',735.30,'222',0.00),('FI300333',300.00,'333',0.00),('FI300502',-100.00,'111',200.00);
/*!40000 ALTER TABLE `tili` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tilitapahtumat`
--

DROP TABLE IF EXISTS `tilitapahtumat`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tilitapahtumat` (
  `tilinumero` varchar(45) DEFAULT NULL,
  `kortinnumero` varchar(45) DEFAULT NULL,
  `paivamaara` datetime DEFAULT NULL,
  `tapahtuma` varchar(45) DEFAULT NULL,
  `summa` decimal(10,2) DEFAULT NULL,
  KEY `tilitapahtumat_tili_idx` (`tilinumero`),
  CONSTRAINT `tilitapahtumat_tili` FOREIGN KEY (`tilinumero`) REFERENCES `tili` (`tilinumero`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tilitapahtumat`
--

LOCK TABLES `tilitapahtumat` WRITE;
/*!40000 ALTER TABLE `tilitapahtumat` DISABLE KEYS */;
INSERT INTO `tilitapahtumat` VALUES ('FI300333','0500CB33C7','2025-04-22 10:42:11','talletus',300.00),('FI300333','0500CB33C7','2025-04-22 10:42:17','nosto',-300.00),('FI300502','060006235F','2025-04-22 17:14:43','talletus',200.00),('FI300502','060006235F','2025-04-22 17:27:17','nosto',-300.00),('FI300222','06000620D0','2025-04-22 17:29:03','talletus',400.00),('FI300222','06000620D0','2025-04-22 17:29:06','talletus',200.00),('FI300502','060006235F','2025-04-22 19:52:47','talletus',200.00),('FI300502','060006235F','2025-04-22 19:53:10','nosto',-300.00),('FI300502','060006235F','2025-04-22 19:54:23','talletus',200.00),('FI300502','060006235F','2025-04-22 20:04:51','nosto',-200.00),('FI300502','060006235F','2025-04-23 08:04:43','talletus',200.00),('FI300502','060006235F','2025-04-23 08:04:51','nosto',-300.00),('FI300502','060006235F','2025-04-23 10:50:34','nosto',-200.00),('FI300502','060006235F','2025-04-23 10:52:13','talletus',200.00),('FI300502','060006235F','2025-04-23 10:52:18','talletus',600.00),('FI300502','060006235F','2025-04-23 11:03:27','nosto',-100.00),('FI300502','060006235F','2025-04-23 14:16:21','talletus',300.00),('FI300502','060006235F','2025-04-23 22:07:44','talletus',200.00),('FI300502','060006235F','2025-04-23 22:07:51','nosto',-300.00),('FI300333','0500CB33C7','2025-04-23 20:53:12','talletus',200.00),('FI300333','0500CB33C7','2025-04-23 23:59:02','talletus',200.00),('FI300333','0500CB33C7','2025-04-23 23:59:06','nosto',-600.00),('FI300222','06000620D0','2025-04-24 00:11:04','talletus',200.00),('FI300222','06000620D0','2025-04-24 00:11:24','nosto',-600.00),('FI300222','06000620D0','2025-04-24 13:07:41','talletus',3.00),('FI300222','06000620D0','2025-04-24 13:07:49','talletus',-6.00),('FI300222','06000620D0','2025-04-24 13:08:00','nosto',-5.00),('FI300222','06000620D0','2025-04-24 13:08:11','talletus',6.00),('FI300222','06000620D0','2025-04-24 13:11:14','talletus',5.00),('FI300222','06000620D0','2025-04-25 13:53:09','talletus',6.00),('FI300222','06000620D0','2025-04-25 13:55:51','talletus',6.00),('FI300222','06000620D0','2025-04-25 13:58:41','talletus',6.00),('FI300222','06000620D0','2025-04-25 14:24:56','talletus',200.00),('FI300222','06000620D0','2025-04-25 14:25:09','talletus',3.00),('FI300222','06000620D0','2025-04-25 14:31:47','talletus',8.00),('FI300222','06000620D0','2025-04-25 14:35:12','talletus',9.20),('FI300222','06000620D0','2025-04-25 14:35:32','nosto',-2.20),('FI300222','06000620D0','2025-04-25 15:12:19','talletus',300.40),('FI300222','06000620D0','2025-04-25 15:12:41','nosto',-200.50),('FI300333','0500CB33C7','2025-04-25 16:11:51','nosto',-1000.00),('FI300333','0500CB33C7','2025-04-25 16:11:58','nosto',-500.00),('FI300502','060006235F','2025-04-25 16:18:57','nosto',-2000.00),('FI300502','060006235F','2025-04-25 16:19:19','nosto',-99.00),('FI300502','060006235F','2025-04-25 16:20:36','nosto',-1.00),('FI300502','060006235F','2025-04-25 16:20:47','talletus',400.00),('FI300222','06000620D0','2025-04-25 16:29:13','talletus',200.50),('FI300222','06000620D0','2025-04-25 16:29:24','nosto',-300.30),('FI300222','06000620D0','2025-04-25 16:34:54','talletus',200.70),('FI300222','06000620D0','2025-04-25 16:35:09','nosto',-300.00),('FI300502','060006235F','2025-04-25 16:36:59','nosto',-300.00),('FI300502','060006235F','2025-04-25 16:37:09','nosto',-100.00),('FI300222','06000620D0','2025-04-25 16:45:17','talletus',200.00),('FI300222','06000620D0','2025-04-25 16:45:41','nosto',-300.30),('FI300502','060006235F','2025-04-25 16:47:41','talletus',500.00),('FI300222','06000620D0','2025-04-25 16:50:25','talletus',300.40),('FI300222','06000620D0','2025-04-25 16:50:46','nosto',-400.20),('FI300502','060006235F','2025-04-25 16:52:37','nosto',-400.00);
/*!40000 ALTER TABLE `tilitapahtumat` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2025-04-25 17:29:19
