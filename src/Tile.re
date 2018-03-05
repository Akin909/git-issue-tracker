open Utils;

let component = ReasonReact.statelessComponent("Tile");

let make = (~repo, _children) => {
  ...component,
  render: _self =>
    <div className="tile__container">
      <div className="tile__content">
        <p className="tile__content__row"> (textEl(repo.full_name)) </p>
        <p className="tile__content__row">
          (textEl("Stargazers Count: "))
          (textEl(string_of_int(repo.stargazers_count)))
        </p>
      </div>
    </div>
};
