const db=require('../database.js');
const bcrypt=require('bcryptjs');

const kortti={
    getAll(callback){
        return db.query('SELECT * FROM kortti',callback);
    },
    getById(id, callback){
        return db.query(' select tunnus, kortinnumero, tili.tilinumero, etunimi, sukunimi, kortinlukija from kortti join asiakas on kortti.omistaja = asiakas.tunnus join tili on kortti.tilinumero = tili.tilinumero where kortinnumero=?',[id],callback);
    },
    getById2(id, callback){
        return db.query(' select * from kortti where kortinnumero=?',[id],callback);
    },
    add(newkortti,callback){
        bcrypt.hash(newkortti.pinkoodi,10,function(err,hashed_password){
            return db.query('INSERT INTO kortti(kortinnumero,pinkoodi,omistaja,tilinumero,kortinlukija) VALUES (?,?,?,?,?)',
            [newkortti.kortinnumero, hashed_password,newkortti.omistaja,newkortti.tilinumero,newkortti.kortinlukija],callback);
        });
    },
    update(id,newData,callback){
        bcrypt.hash(newData.pinkoodi,10,function(err,hashed_password){
        return db.query('UPDATE kortti SET kortinnumero=?,pinkoodi=?,omistaja=?,tilinumero=?,kortinlukija=? WHERE kortinnumero=?',
            [newData.kortinnumero, hashed_password, newData.omistaja, newData.tilinumero, newData.kortinlukija, id],callback)
         } );
    },
    update2(id,newData,callback){
       
        return db.query('UPDATE kortti SET kortinnumero=?,pinkoodi=?,omistaja=?,tilinumero=?,kortinlukija=? WHERE kortinnumero=?',
            [newData.kortinnumero, newData.pinkoodi, newData.omistaja, newData.tilinumero, newData.kortinlukija, id],callback)
        
    },
    delete(id,callback){
        return db.query('DELETE FROM kortti WHERE kortinnumero=?',id,callback);
    },
    checkPassword(id,callback){
        return db.query('SELECT pinkoodi FROM kortti WHERE kortinnumero=?',[id],callback);
    }
}

module.exports=kortti;