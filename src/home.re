open Utils;

type action =
  | ReposFetched(repo)
  | FetchRepos
  | ReposFetchFailed(string);

type state =
  | Loading
  | Loaded(repo)
  | Error(string);

let component = ReasonReact.reducerComponent("Home");

module Tile = {
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
};

module Title = {
  let component = ReasonReact.statelessComponent("Title");
  let make = (~text: string, _children) => {
    ...component,
    render: _self => <h1 className="title"> (textEl(text)) </h1>
  };
};

let make = _children => {
  ...component,
  initialState: () => Loading,
  reducer: (action, _state) =>
    switch action {
    | FetchRepos =>
      ReasonReact.UpdateWithSideEffects(
        Loading,
        (
          self =>
            Js.Promise.(
              Fetch.fetch("https://api.github.com/onivim/oni")
              |> then_(Fetch.Response.json)
              |> then_(json =>
                   json
                   |> parseRepoJson
                   |> (repo => self.send(ReposFetched(repo)))
                   |> resolve
                 )
              |> catch(_err =>
                   Js.Promise.resolve(
                     self.send(
                       ReposFetchFailed(
                         "Sorry I was unable to get the repo data"
                       )
                     )
                   )
                 )
              |> ignore
            )
        )
      )
    | ReposFetched(repo) => ReasonReact.Update(Loaded(repo))
    | ReposFetchFailed(error) => ReasonReact.Update(Error(error))
    },
  didMount: self => {
    self.send(FetchRepos);
    ReasonReact.NoUpdate;
  },
  render: self =>
    switch self.state {
    | Loading => <div> (textEl("Loading...")) </div>
    | Error(error) => <div> (textEl(error)) </div>
    | Loaded(repo) =>
      <div className="container">
        <Title text="Git Issue Tracker" />
        <Tile repo />
      </div>
    }
};
