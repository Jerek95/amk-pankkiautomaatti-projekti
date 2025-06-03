const db=require('../database.js');

const tilitapahtumat={
    getAll(callback){
        return db.query(`SELECT tilinumero,kortinnumero,DATE_FORMAT(paivamaara, '%Y-%m-%d %H:%i:%s') AS paivamaara, tapahtuma, summa FROM tilitapahtumat`,callback);
    },
    getById(id, callback){
        return db.query(`SELECT tilinumero, kortinnumero, DATE_FORMAT(paivamaara, '%Y-%m-%d %H:%i:%s') AS paivamaara, tapahtuma, summa FROM tilitapahtumat WHERE tilinumero = ?`,[id],callback);
    },
    add(newtilitapahtumat,callback){
            return db.query('INSERT INTO tilitapahtumat(tilinumero,kortinnumero,paivamaara,tapahtuma,summa) VALUES (?,?,?,?,?)',
            [newtilitapahtumat.tilinumero, newtilitapahtumat.kortinnumero,newtilitapahtumat.paivamaara,newtilitapahtumat.tapahtuma,newtilitapahtumat.summa],callback);
    },
    update(id,newData,callback){
        return db.query('UPDATE tilitapahtumat SET tilinumero=?,kortinnumero=?,paivamaara=?,tapahtuma=?,summa=? WHERE tilinumero=?',
            [newData.tilinumero, newData.kortinnumero, newData.paivamaara, newData.tapahtuma, newData.summa, id],callback
        );
    },
    delete(id,callback){
        return db.query('DELETE FROM tilitapahtumat WHERE tilinumero=?',id,callback);
    }
}

module.exports=tilitapahtumat;