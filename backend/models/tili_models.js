const db=require('../database.js');

const tili={
    getAll(callback){
        return db.query('SELECT * FROM tili',callback);
    },
    getById(id, callback){
        return db.query('SELECT * FROM tili WHERE tilinumero=?',[id],callback);
    },
    add(newtili,callback){
            return db.query('INSERT INTO tili(tilinumero,saldo,omistaja,luottoraja) VALUES (?,?,?,?)',
            [newtili.tilinumero, newtili.saldo,newtili.omistaja,newtili.luottoraja],callback);
    },
    update(id,newData,callback){
        return db.query('UPDATE tili SET tilinumero=?,saldo=?,omistaja=?,luottoraja=? WHERE tilinumero=?',
            [newData.tilinumero, newData.saldo, newData.omistaja, newData.luottoraja, id],callback
        );
    },
    delete(id,callback){
        return db.query('DELETE FROM tili WHERE tilinumero=?',id,callback);
    }
}

module.exports=tili;