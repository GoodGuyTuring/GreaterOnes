use std::env;
use std::num::ParseIntError;

type Matrix = Vec<Vec<i64>>;

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() != 4 {
        println!("Falsche Anzahl an Parametern. Bitte erneut versuchen");
        return ();
    }
    if &args[2] != "+" && &args[2] != "*" {
        println!("Instructions unclear");
        return ();
    }

    //wandelt die erste Eingabe in eine Integer Matrix um und überprüft das Format auf Korrektheit

    let mut zer: Vec<&str> = args[1].split(';').collect();
    let mut matrix1: Matrix = Matrix::new();

    let mut k: i64 = -1;

    for i in 0..zer.len() {
        matrix1.push(Vec::new());
        let mut sub_zer: Vec<&str> = zer[i].split(",").collect();
        if k < 0 {
            k = sub_zer.len() as (i64);
        } else {
            if k != sub_zer.len() as (i64) {
                println!("Fehler: Matrizen haben fehlerhaftes Format");
                return ();
            }
        }
        for j in 0..sub_zer.len() {
            match sub_zer[j].parse::<i64>() {
                Ok(n) => matrix1[i].push(n),
                Err(e) => return (),
            }
        }
    }

    //wandelt die zweite Eingabe in Integermatrix um und prüft die Eingabe

    k = -1;
    let mut zer1: Vec<&str> = args[3].split(';').collect();
    let mut matrix2: Vec<Vec<i64>> = Vec::new();

    for i in 0..zer1.len() {
        matrix2.push(Vec::new());
        let mut sub_zer: Vec<&str> = zer1[i].split(",").collect();


        for j in 0..sub_zer.len() {
            match sub_zer[j].parse::<i64>() {
                Ok(n) => matrix2[i].push(n),
                Err(e) => return (),
            }
        }
        if k < 0 {
            k = matrix2[i].len() as (i64);
        } else {
            if k != matrix2[i].len() as (i64) {
                println!("Fehler: Matrizen haben fehlerhaftes Format");
                return ();
            }
        }
    }

    if &args[2] == "+" {
        mat_print(mat_add(matrix1, matrix2));
        return ();
    } else if &args[2] == "*" {
        mat_print(mat_mul(matrix1, matrix2));
        return ();
    } else {
        println!("Error");
        return ();
    }
}

fn mat_print(mat: Matrix) {
    for i in 0..mat.len() {              //i = Reihen der Matrix
        for j in 0..mat[i].len() {       //j = Spalten der Matrix
            print!("{}", mat[i][j]);              //Print Mat[i],[j]
            if j < mat[i].len() - 1 {             //print "," wenn nicht am Ende der Reihe
                print!(",");
            }
        }
        if i < mat.len() - 1 {               //print ";" wenn nicht Ende der Spalten
            print!(";");
        }
    }
    println!();
}

fn mat_mul(mat1: Matrix, mat2: Matrix) -> Matrix {
    //wenn Parameter ungeeignete Dimensionen haben
    if mat1[0].len() != mat2.len() {
        println!("Spalten und Reihen stimmen nicht überein");
        return Matrix::new();
    } else {
        //multiplizieren
        let mut ret_mat = Matrix::new();

        //Erechnen jedes einzelnen Eintrags zeilenweise von l nach r
        for i in 0..mat1.len() {

            //neue Zeile erstellen
            ret_mat.push(Vec::new());

            for k in 0..mat2[0].len() {
                let mut new_entry: i64 = 0;

                //Eintrag berechnen
                for j in 0..mat1[0].len() {
                    new_entry += mat1[i][j] * mat2[j][k];
                }
                //Eintrag hinzufügen
                ret_mat[i].push(new_entry);
            }
        }
        return ret_mat;
    }
}

fn mat_add(mat1: Matrix, mat2: Matrix) -> Matrix {
    //unpassende Dimensionen
    if mat1[0].len() != mat2[0].len() || mat2.len() != mat2.len() {
        return Matrix::new();
    } else {
        let mut ret_mat = Matrix::new();

        //Elementweise addieren
        for i in 0..mat1.len() {
            ret_mat.push(Vec::new());
            for j in 0..mat1[0].len() {
                ret_mat[i].push(mat1[i][j] + mat2[i][j]);
            }
        }
        return ret_mat;
    }
}