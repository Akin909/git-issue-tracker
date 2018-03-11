open Utils;

type action =
  | FetchRepos
  | FetchIssues
  | FetchedIssues(list(issue))
  | ReposFetched(repo)
  | URLChanged(string)
  | ReposFetchFailed(string);

type remote =
  | Loading
  | Loaded(repo)
  | Error(string);

type state = {
  error: string,
  loading: bool,
  issues: option(list(issue)),
  repo: remote
};

let renderIssues = (issues: option(list(issue))) =>
  <ul className="issue__list">
    (
      switch issues {
      | Some(issues) =>
        List.map(issue => <Issue key=string_of_int(issue.number) issue />, issues)
        |> Array.of_list
        |> ReasonReact.arrayToElement
      | None => ReasonReact.nullElement
      }
    )
  </ul>;

let component = ReasonReact.reducerComponent("Home");

let make = _children => {
  ...component,
  initialState: () => {error: "", loading: false, issues: None, repo: Loading},
  subscriptions: self => [
    Sub(
      () =>
        ReasonReact.Router.watchUrl(url =>
          switch (url.hash, url.path) {
          | (hash, _path) => self.send(URLChanged(hash))
          }
        ),
      ReasonReact.Router.unwatchUrl
    )
  ],
  reducer: (action, state) =>
    switch action {
    | FetchRepos =>
      ReasonReact.UpdateWithSideEffects(
        {...state, loading: true},
        (
          self =>
            Js.Promise.(
              Fetch.fetch(repoUrl ++ repoOfChoice)
              |> then_(Fetch.Response.json)
              |> then_(json =>
                   json
                   |> parseRepoJson
                   |> (repo => self.send(ReposFetched(repo)))
                   |> (_json => self.send(FetchIssues) |> resolve)
                 )
              |> catch(err => {
                   Js.log(err);
                   Js.Promise.resolve(
                     self.send(
                       ReposFetchFailed(
                         "Sorry I was unable to get the repo data"
                       )
                     )
                   );
                 })
              |> ignore
            )
        )
      )
    | FetchIssues =>
      ReasonReact.UpdateWithSideEffects(
        state,
        (
          self =>
            Js.Promise.(
              Fetch.fetch(repoUrl ++ repoOfChoice ++ "/issues")
              |> then_(Fetch.Response.json)
              |> then_(json =>
                   json
                   |> parseIssuesJson
                   |> Array.to_list
                   |> (issues => self.send(FetchedIssues(issues)))
                   |> resolve
                 )
              |> ignore
            )
        )
      )
    | ReposFetched(repo) =>
      ReasonReact.Update({...state, repo: Loaded(repo), loading: false})
    | ReposFetchFailed(error) =>
      ReasonReact.Update({...state, error, repo: Error("Failed to load")})
    | FetchedIssues(issues) =>
      ReasonReact.Update({...state, issues: Some(issues)})
    | URLChanged(url) =>
      let () = Js.log(url);
      ReasonReact.NoUpdate;
    },
  didMount: self => {
    self.send(FetchRepos);
    ReasonReact.NoUpdate;
  },
  render: ({state}) =>
    <div className="main__content">
      (
        switch state.repo {
        | Error(message) => <div> (textEl(message)) </div>
        | Loading => <div> (textEl("Loading....")) </div>
        | Loaded(repo) => <Tile repo />
        }
      )
      (renderIssues(state.issues))
    </div>
};
