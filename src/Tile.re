open Utils;

[@bs.module] external onivim : string = "./oni-logo.png";

let component = ReasonReact.statelessComponent("Tile");

/* TODO Find out how to make this one function */
let renderNumberItem = (item: option(int)) =>
  switch item {
  | Some(item) => textEl(string_of_int(item))
  | None => textEl("")
  };

let renderStrItem = (item: option(string)) =>
  switch item {
  | Some(item) => textEl(item)
  | None => textEl("")
  };

let make = (~repo, _children) => {
  ...component,
  render: _self =>
    <div className="tile__container">
      <div className="tile__content">
        <img src=onivim alt="Onivim logo" className="image image-small"/>
        <p className="tile__content__row title"> (textEl(repo.full_name)) </p>
        <p className="tile__content__row">
          <span className="tile__content__label">
            (textEl("Description: "))
          </span>
          (renderStrItem(repo.description))
        </p>
        <p className="tile__content__row">
          <span className="tile__content__label">
            (textEl("Stargazers Count: "))
          </span>
          (renderNumberItem(repo.stargazers_count))
        </p>
        <p className="tile__content__row">
          <span className="tile__content__label">
            (textEl("Open Issues: "))
          </span>
          (textEl(string_of_int(repo.open_issues_count)))
        </p>
        <p className="tile__content__row">
          <span className="tile__content__label">
            (textEl("Language: "))
          </span>
          (textEl(repo.language))
        </p>
      </div>
    </div>
};
