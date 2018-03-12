open Utils;

[@bs.module] external github : string = "./github.png";

let component = ReasonReact.statelessComponent("Home");

module Title = {
  let component = ReasonReact.statelessComponent("Title");
  let make = (~text: string, _children) => {
    ...component,
    render: _self =>
      <header className="title-container">
        <img src=github alt="Github Logo" className="image image--github" />
        <h1 className="title"> (textEl(text)) </h1>
      </header>
  };
};

let make = _children => {
  ...component,
  render: _self =>
    <div className="container">
      <Title text="Git Issue Tracker" />
      <Issues />
    </div>
};
