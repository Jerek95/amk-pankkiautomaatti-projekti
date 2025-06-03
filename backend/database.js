const mysql=require('mysql2');
const ConnectionString='mysql://bankuser:bankpass@127.0.0.1:3306/bank_database';
const connection = mysql.createPool(ConnectionString);

module.exports=connection;

/*
Luodaan tunnus ja annetaan oikeudet
CREATE USER bankuser@localhost IDENTIFIED BY 'bankpass';
GRANT ALL ON bank_database.* TO bankuser@localhost;
*/