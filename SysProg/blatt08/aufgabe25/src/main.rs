use std::env;
use std::num::ParseIntError;
use std::thread;

type Matrix = Vec<Vec<i64>>;

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() != 4 || args.len() != 5 {
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

    if args.len() == 5{
        // mit thread zahl aufrufen
        let mut threadNum :i64 = 0;
        match args[4].parse::<i64>() {
            Ok(n) => threadNum = n,
            Err(e) => return (),
        }
        if &args[2] == "+" {
            mat_print(mat_add(matrix1, matrix2));
            return ();
        } else if &args[2] == "*" {
            mat_print(mat_mul_thread(matrix1, matrix2, threadNum));
            return ();
        } else {
            println!("Error");
            return ();
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

fn mat_mul_thread(mat1: Matrix, mat2: Matrix, thread_count: i64) -> Matrix{
    let mut end_index: i64 = 0;
    let mut anfangs_index: i64 = 0;
    let mut anzahl: i64 = (mat1[0].len() * mat2.len()) as i64;
    let mut rest_tmp: i64 = anzahl % thread_count;
    let mut thread_array : Vec<thread::JoinHandle<_>> = Vec::with_capacity(thread_count as usize);

    if mat1[0].len() != mat2.len() {
        println!("Spalten und Reihen stimmen nicht überein");
        return Matrix::new();
    } else {
        //multiplizieren
        let mut ret_mat = Matrix::new();
        //Erechnen jeden Eintrag verteilt auf Threads
        for i in 0.. thread_count-1{
            end_index = anfangs_index + anzahl / thread_count;
            if rest_tmp != 0{
                end_index+=1;
                rest_tmp -= 1;
            }
            thread_array[i as usize] = thread::spawn(||{
                mat_mul_part(mat1, mat2, &mut ret_mat, anfangs_index, end_index)
            });
            //todo thread mit parametern erstellen und laufen
            anfangs_index = end_index + 1;
        }

        for i in 0 .. thread_count-1{
            thread_array[i as usize].join();
        }

        return ret_mat;
    }
}

fn mat_mul_part(mat1: Matrix, mat2: Matrix, result: &mut Matrix, anfangs_index: i64, end_index: i64) {
    let n: i64 = result.len() as i64;
    let m: i64 = result[0].len() as i64;
    //i ist Zeile
    for i in anfangs_index / m .. end_index / m +1{
        if i == anfangs_index / m {
            //k ist Spalte
            for k in anfangs_index % m..m - 1 {
                let mut new_entry: i64 = 0;

                //Eintrag berechnen
                for j in 0..mat1[0].len() {
                    new_entry += mat1[i as usize][j as usize] * mat2[j as usize][k as usize];
                }
                //Eintrag einfügen
                result[i as usize][k as usize] = new_entry;
            }
        }
        else if i == end_index / m {
            for k in 0..end_index % m +1{
                let mut new_entry: i64 = 0;

                //Eintrag berechnen
                for j in 0..mat1[0].len() {
                    new_entry += mat1[i as usize][j as usize] * mat2[j as usize][k as usize];
                }
                //Eintrag einfügen
                result[i as usize][k as usize] = new_entry;
            }
        }
        else{
            for k in 0.. m-1{
                let mut new_entry: i64 = 0;

                //Eintrag berechnen
                for j in 0..mat1[0].len() {
                    new_entry += mat1[i as usize][j as usize] * mat2[j as usize][k as usize];
                }
                //Eintrag einfügen
                result[i as usize][k as usize] = new_entry;
            }
        }
    }
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
