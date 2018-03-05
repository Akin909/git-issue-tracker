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

let defaultHeaders = [%bs.raw {|
{
  username: "Akin909",
}
|}];

let headers = Fetch.HeadersInit.make(defaultHeaders);

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
    | Loaded(repo) => <Tile repo />
    }
};
