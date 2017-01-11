output_string stdout " <html> <head> <title>  ";;

        open Core.Std;;

        let (--) i j = 
          let rec aux n acc =
            if n < i then acc else aux (n-1) (n :: acc)
          in aux j [];;


        let matrix_multiply x y =
          let x0 = Array.length x
                   and y0 = Array.length y in
          let y1 = if y0 = 0 then 0 else Array.length y.(0) in
          let z = Array.make_matrix x0 y1 0 in
          for i = 0 to x0-1 do
            for j = 0 to y1-1 do
              for k = 0 to y0-1 do
                z.(i).(j) <- z.(i).(j) + x.(i).(k) * y.(k).(j)
              done
            done
          done;
          z;;

        let matrix_print x =
          let len = Array.length x in
          for i = 0 to len - 1 do
            let wid = Array.length x.(i) in
            for j = 0 to wid - 1 do
              printf "%d, " x.(i).(j)
            done;
            printf "<br />";
          done;
          ();;

        let m1 = Array.make_matrix 10 10 2
        let m2 = Array.make_matrix 10 10 2

        let m3 = matrix_multiply m1 m2

        let testval = 41989;;
        let is_prime n =
          let rec testdiv m test =
            if test > 1 then
              begin
                if m mod test = 0 then true
                else testdiv m (test - 2)
              end
            else false in
        if testdiv n (n - 1) = true then false else true;;
        printf "Is %d prime?" testval;;
        
output_string stdout " </title> </head> <body> <h3>Is \"  ";;
 printf "%d" testval;; 
output_string stdout " \" prime?</h3><br /> <h1>  ";;
 printf (if is_prime testval then "Yes" else "No");; 
output_string stdout " </h1> <h1>  ";;
 matrix_print m1;; 
output_string stdout " <br />TIMES<br />  ";;
 matrix_print m2;; 
output_string stdout " <br /> EQUALS<br />  ";;
 matrix_print m3; 
output_string stdout " </h1> </body> </html>  ";;
