
/* let str_json_sample = "[{\"value\": 43}, {\"event\": \"bang\", \"value\": 44}]";
let json = Ezjsonm.from_string str_json_sample; */


module Aggregate = {
  open List;
  let fold_left_exn f l =>
  switch l {
  | [] => failwith "empty list";
  | [h, ...t] => fold_left f h t; 
  };
  let sum = fold_left (+.) 0.;
  let max = fold_left_exn Pervasives.max;
  let min = fold_left_exn Pervasives.min;
  let count xs => float_of_int (length xs);
};


let from_json json => {
  open Ezjsonm;  
  List.map 
    (fun x => get_float (find x ["value"])) 
    (get_list (fun x => x) json);  
};

let to_json result => {
  open Ezjsonm;
  dict [("result", `Float result)];
};

let sum json => {
  from_json json |> Aggregate.sum |> to_json;
};

let mean json => {
  open Aggregate;
  let xs = from_json json;
  let n = count xs;
  xs |> sum |> fun total => (total /. n) |> to_json;
};

let min json => {
  from_json json |> Aggregate.min |> to_json;
};

let max json => {
  from_json json |> Aggregate.max |> to_json;
};

let count json => {
  from_json json |> Aggregate.count |> to_json;
};