open Utils;

let component = ReasonReact.statelessComponent("Home");

let tile = () =>
  <div className="tile__container">
    <div className="tile__content">
      (ReasonReact.stringToElement("content"))
    </div>
  </div>;

module Title = {
  let component = ReasonReact.statelessComponent("Title");
  let make = (~text: string, _children) => {
    ...component,
    render: _self => <h1 className="title"> (textEl(text)) </h1>
  };
};

let make = _children => {
  ...component,
  didMount: _self =>
    Js.Promise.(
      Fetch.fetch("https://api.github.com/onivim/oni")
      |> then_(Fetch.Response.json)
      |> then_(json => parseRepoJson(json) |> resolve)
    ),
  render: _self =>
    <div className="container">
      <Title text="Git Issue Tracker" />
      (tile())
    </div>
};
