output_string stdout " <div class = \"usermessage\">  ";;

open Core.Std;;
open Sys;;

let unoption_string s =
  match s with
  | Some str -> str
  | None -> "";;

let (--) i j = 
  let rec aux n acc =
    if n < i then acc else aux (n-1) (n :: acc)
  in aux j [];;

output_string stdout (unoption_string (Sys.getenv "ducklet_post"));;

output_string stdout " </div>  ";;
