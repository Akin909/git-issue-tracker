let textEl = ReasonReact.stringToElement;

type repo = {
  full_name: string,
  stargazers_count: int,
  html_url: string
};

let parseRepoJson = json : repo =>
  Json.Decode.{
    full_name: json |> field("full_name", string),
    stargazers_count: json |> field("stargazers_count", int),
    html_url: json |> field("html_url", string)
  };

let fetchIssues = (url: string) =>
  Js.Promise.(
    Fetch.fetch(url)
    |> then_(Fetch.Response.json)
    |> then_(json => parseRepoJson(json) |> resolve)
    |> resolve
  );
