open Utils;

let component = ReasonReact.statelessComponent("Tile");

let renderNumberItem = (item: option(int)) =>
  switch item {
    | Some(item) => textEl(string_of_int(item))
    | None => textEl("")
  };

let make = (~repo, _children) => {
  ...component,
  render: _self =>
    <div className="tile__container">
      <div className="tile__content">
        <p className="tile__content__row"> (textEl(repo.full_name)) </p>
        <p className="tile__content__row">
          (textEl("Stargazers Count: "))
          (renderNumberItem(repo.stargazers_count))
        </p>
      </div>
    </div>
};
