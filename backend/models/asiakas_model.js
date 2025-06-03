const db=require('../database.js');

const asiakas={
    getAll(callback){
        return db.query('SELECT * FROM asiakas',callback);
    },
    getById(id, callback){
        return db.query('SELECT * FROM asiakas WHERE tunnus=?',[id],callback);
    },
    add(newasiakas,callback){
            return db.query('INSERT INTO asiakas(tunnus,etunimi,sukunimi,osoite,puhelinnumero) VALUES (?,?,?,?,?)',
            [newasiakas.tunnus, newasiakas.etunimi,newasiakas.sukunimi,newasiakas.osoite,newasiakas.puhelinnumero],callback);
    },
    update(id,newData,callback){
        return db.query('UPDATE asiakas SET tunnus=?,etunimi=?,sukunimi=?,osoite=?,puhelinnumero=? WHERE tunnus=?',
            [newData.tunnus, newData.etunimi, newData.sukunimi, newData.osoite, newData.puhelinnumero, id],callback
        );
    },
    delete(id,callback){
        return db.query('DELETE FROM asiakas WHERE tunnus=?',id,callback);
    }
}

module.exports=asiakas;